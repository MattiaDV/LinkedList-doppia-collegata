public class Main {
    public static void main(String[] args) {
        Core core = new Core();
        int risultato = core.somma(5, 3);
        int mol = core.moltiplica(10, 10);
        float div = core.dividi(10, 5);
        System.out.println("Risultato: " + risultato);
        System.out.println("Molti: " + mol);
        System.out.println("Divi: " + div);
    }
}