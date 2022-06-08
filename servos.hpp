namespace Servos {
    extern int our_count;
    extern int rival_count;

    void setup_servos();

    namespace S1 {
        void take_rival();
        void take_ours();
        void finish_taking();
    }
    namespace S2 {
        void open();
        void close();
    }
}