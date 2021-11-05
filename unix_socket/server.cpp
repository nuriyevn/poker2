#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "JSON.h"


 
 
#include "server.hpp"

/*
 * Create an application that listens on a UNIX domain socket for events in the form of strings in the standard JSON format.
 * Each event should be processed by one of N threads. Each thread should perform an operation with the event that might take 
 * up to several seconds to be executed and the log its results into one common text file.
*/


// g++ -I./json server.cpp main.cpp json/JSON.cpp json/JSONValue.cpp -pthread -o server && ./server

void* factorial(void* p)

{
  int n = *(int*)p;
  
  
  int64_t  fact = 1;
  if (n > 20)
    n = 20;
  
  for (int i = 1; i <= n; i++)
  {
      fact = fact * i;
  }
  
  usleep(3000000);
  
  pid_t x = syscall(__NR_gettid);
  printf("Thread id=%d, Factorial %d requested , the result is %jd\n", x, n,  fact);
  

}

void *SocketThread::run_server() {
  fprintf(stdout, "Starting thread server...\n");
  if (pthread_mutex_trylock(&mutex_) != 0) {
    fprintf(stderr, "Error: Failed to lock mutex thread\n");
    return NULL;
  }

  cleanup_socket();

  fprintf(stdout, "Creating socket...\n");
  if ((sockfd_ = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Error: Failed to create socket\n");
    return NULL;
  }

  fprintf(stdout, "Initializing socket...\n");
  struct sockaddr_un serv_addr;
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sun_family = AF_UNIX;
  strcpy(serv_addr.sun_path, socket_path_.c_str());

  fprintf(stdout, "Binding socket...\n");
  if (bind(sockfd_, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
    fprintf(stderr, "Error: Failed to bind socket\n");
    return NULL;
  }

  fprintf(stdout, "Listening socket...\n");
  if (listen(sockfd_, MAX_BACKLOG) == -1) {
    fprintf(stderr, "Error: Failed to listen to socket\n");
    return NULL;
  }

  struct sockaddr_un cli_addr;
  char buffer[BUFFER_SIZE + 1];
  while (true) {
    socklen_t cli_len = sizeof(cli_addr);
    fprintf(stdout, "Accepting socket...\n");
    if ((curr_sock_fd_ = accept(sockfd_, (struct sockaddr *)&cli_addr, &cli_len)) == -1) {
      fprintf(stderr, "Error: Failed to accept socket\n");
      continue;
    }
    
    
    
    bzero(buffer, BUFFER_SIZE + 1);
    if (read(curr_sock_fd_, buffer, BUFFER_SIZE) == -1) {
      fprintf(stderr, "Error: Failed to read socket\n");
      continue;
    }
      
    int number = parse_json(buffer);
    printf("number from client %d", number);
    
    
    pthread_t thread;
	
      
    int iret1;
    
    iret1 = pthread_create(&thread, NULL, factorial, 
    (void*)&number);
    
    printf("Thread returns: %d\n", iret1);
    
    pthread_detach(thread);
    //pthread_join(thread, NULL);
    
    
    printf( "=> read buffer [%s]\n", buffer);
    close(curr_sock_fd_);
  }
}


const wchar_t *ctow(const char *buf, wchar_t *output) {
    wchar_t cr = *output;
    while (*buf) {
        *output++ = *buf++;
    }
    *output = 0;
    return (wchar_t*)cr;
}

int SocketThread::parse_json(char* buffer)
{
     //const wchar_t* jsonSample = L"{ \"event\": \"calc\", \"function\":\"fact\",  \"data\": 7 }";
     
    wchar_t rootStr[BUFFER_SIZE + 1] = {0};
    ctow(buffer, rootStr );
    JSONValue *root = JSON::Parse(rootStr);
    
    bool isObject = root->IsObject();
    printf("%s", isObject ? "Object" : "not Object");
    
    if (isObject)
    {	
      bool hasChild = root->HasChild(L"event");
      if (hasChild)
      {	
        JSONValue* eventJsonValue = root->Child(L"event");
        
        if (eventJsonValue->AsString() == std::wstring(L"calc"))
        {
          printf("it's %ls", eventJsonValue->AsString().c_str());
        }
      }
      
      if (root->HasChild(L"data"))
      {
        return int(root->Child(L"data")->AsNumber());
      }
    }
    
    
    return 0;
}



SocketThread* SocketThread::instance_ = NULL;

SocketThread* SocketThread::Instance() {
  if (!instance_) {
    instance_ = new SocketThread;
  }
  return instance_;
}

SocketThread::SocketThread()
  : pid_(0),
    socket_path_(".socket"),
    sockfd_(0),
    curr_sock_fd_(0) {
  fprintf(stdout, "Init mutex...\n");
  pthread_mutex_init(&mutex_, NULL);
}

SocketThread::~SocketThread() {
  stop();
}

bool SocketThread::start() {
  fprintf(stdout, "Creating thread...\n");
  if (pthread_create(&pid_, NULL, &(SocketThread::thread_starter), this) != 0) {
    fprintf(stderr, "Error: Failed to start thread\n");
    return false;
  }
  fprintf(stdout, "Thread created\n");
  handle_signals();
  return true;
}

void SocketThread::stop() {
  fprintf(stdout, "Destroying mutex...\n");
  pthread_mutex_destroy(&mutex_);
  if (pid_) {
    pthread_cancel(pid_);
    pid_ = 0;
  }
  if (sockfd_) {
    close(sockfd_);
    sockfd_ = 0;
  }
  cleanup_socket();
}

void SocketThread::set_socket_path(const std::string& path) {
  socket_path_ = path;
}

void *SocketThread::thread_starter(void *obj) {
  fprintf(stdout, "Starting thread starter...\n");
  return reinterpret_cast<SocketThread *>(obj)->run_server();
}

void SocketThread::thread_stopper(int sig, siginfo_t *siginfo, void *context) {
  fprintf(stdout, "Starting thread stopper...\n");
  Instance()->stop();
  exit(0);
}



void SocketThread::handle_signals() {
  struct sigaction act;
  memset(&act, '\0', sizeof(act));
  act.sa_sigaction = &thread_stopper;
  act.sa_flags = SA_SIGINFO;
  if (sigaction(SIGTERM, &act, NULL) == -1) {
    printf("Failed to register SIGTERM\n");
  }
  if (sigaction(SIGINT, &act, NULL) == -1) {
    printf("Failed to register SIGTINT\n");
  }
}

void SocketThread::cleanup_socket() {
  if (access(socket_path_.c_str(), F_OK) != -1) {
    printf("Cleanup socket\n");
    unlink(socket_path_.c_str());
  }
}
