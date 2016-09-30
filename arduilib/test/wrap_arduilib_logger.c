#define UNUSED(x) (void)(x)

void __wrap_arduilib_log_error(unsigned long time, int error_code, char* msg, ...) {
    UNUSED(time); UNUSED(error_code); UNUSED(msg);
}
