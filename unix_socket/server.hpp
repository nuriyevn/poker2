#include <pthread.h>
#include <signal.h>
#include <string>

#define CLIENT_SOCKET_FILE "client.socket"
#define SERVER_SOCKET_FILE ".socket"


class SocketThread {
public:
  static SocketThread* Instance();

  bool start();
  void stop();
  void set_socket_path(const std::string& path);

  enum {
    MAX_BACKLOG = 20,
    BUFFER_SIZE = 8192
  };

private:
  SocketThread();
  ~SocketThread();

  static void* thread_starter(void* obj);
  static void thread_stopper(int sig, siginfo_t* siginfo, void* context);
  void* run_server();
  void handle_signals();
  void cleanup_socket();
  //int64_t factorial(int n);
  int parse_json(char* buffer);

  pthread_t pid_;
  pthread_mutex_t mutex_;
  std::string socket_path_;
  int sockfd_;
  int curr_sock_fd_;
  static SocketThread* instance_;
};
