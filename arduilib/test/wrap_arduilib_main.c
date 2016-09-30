#define UNUSED(x) (void)(x)
void __wrap_arduilib_update_loop() {
    // Do nothing.
}

void __wrap_arduilib_exit(int code) {
    UNUSED(code);
    // Do nothing.
}
