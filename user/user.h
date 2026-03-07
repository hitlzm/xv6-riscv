struct stat;
struct rtcdate;

// system calls
int fork(void);  //创建子进程
int exit(int) __attribute__((noreturn));//结束当前进程
int wait(int*);   //等待子进程结束
int pipe(int*);   //创建管道
int write(int, const void*, int);
int read(int, void*, int);  //从文件读取数据
int close(int);
int kill(int); //杀死指定线程
int exec(char*, char**);    //加载并运行新程序
int open(const char*, int);  // 打开文件
int mknod(const char*, short, short);  //创建设备文件
int unlink(const char*);  //删除文件
int fstat(int fd, struct stat*);  //获取文件信息
int link(const char*, const char*); //创建硬链接
int mkdir(const char*);
int chdir(const char*);    //切换目录
int dup(int);   //复制文件描述符
int getpid(void);  //获取当前进程的PID
char* sbrk(int);   // 调整进程堆大小
int sleep(int);    // 进程睡眠
int uptime(void);  //返回系统启动后的tick数

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);  //字符串复制
void *memmove(void*, const void*, int);  //安全内存复制
char* strchr(const char*, char c);   //查找字符第一次出现位置
int strcmp(const char*, const char*); //字符串比较
void fprintf(int, const char*, ...);   //指定文件描述符打印
void printf(const char*, ...);  //标准输出打印
char* gets(char*, int max);    //读取一行输入
uint strlen(const char*);     //字符串长度
void* memset(void*, int, uint);  //填充内存
void* malloc(uint);     //动态申请内存
void free(void*);       //释放内存
int atoi(const char*);  //字符串转整数
int memcmp(const void *, const void *, uint);  //比较内存
void *memcpy(void *, const void *, uint);  //内存复制
