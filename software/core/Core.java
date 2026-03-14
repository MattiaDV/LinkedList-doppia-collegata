public class Core {
    static {
        System.loadLibrary("funzioni"); // carica funzioni.dll
    }

    // Dichiarazione della funzione C
    public native int somma(int a, int b);
    public native int moltiplica(int a, int b);
    public native float dividi(int a, int b);
}
