extern uint64_t stopStart(int line, char *file, char *fmt, ...);
#define MARK(...) stopStart( __LINE__,__FILE__, __VA_ARGS__)
void mem_report(void);


