import java.util.Scanner;

interface Services {
    boolean InputSanization(String UserInput);
    String requestInput(Scanner scanner);
}

public class Server implements Services {
    public boolean InputSanization(String UserInput) {
        if (!UserInput.matches("[a-zA-Z0-9_ ]+")) {
            return false;
        }

        System.out.println("Parola andata a buon fine: " + UserInput);
        return true;
    }

    public String requestInput(Scanner scanner) {
        System.out.println("Inserire parola: ");
        String parola = scanner.nextLine();
        return parola;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Server s = new Server();
        String parola;
        boolean valido;

        do {
            parola = s.requestInput(scanner);
            valido = s.InputSanization(parola);

            if (!valido) {
                System.out.println("Hai scritto una cosa indecente!");
            }

        } while (!valido);

        System.out.println("Perfetto tutto funzionante!");
        scanner.close();
    }
}