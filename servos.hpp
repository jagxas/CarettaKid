namespace Servos {
    extern int puck_count;

    void setup_servos();

    namespace S1 {
        void dont_take_it();
        void take_it();
    }
    namespace S2 {
        void open();
        void close();
    }
}