import java.util.Scanner;
import java.net.http.*;
import java.net.URI;

interface Services {
    void InputValidation(String UserInput);
}

abstract class ServicesPlus {
    abstract void DbConnection();
}

public class Security extends ServicesPlus implements Services {
    public void DbConnection() {
        try {
            final String url = System.getenv("DB_URL");
            final String anon = System.getenv("DB_ANON");

            HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .header("apikey", anon)
                .header("Authorization", "Bearer " + anon)
                .GET()
                .build();
            HttpClient client = HttpClient.newHttpClient();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            System.out.println(response.body());
        } catch (Exception e) {
            System.out.println("Impossibile connettersi al DB!: " + e.getMessage());
        }
    }

    public void InputValidation(String UserInput) {
        if (!UserInput.matches("[a-zA-Z0-9_ ]+")) {
            throw new IllegalArgumentException("Hai inserito caratteri non validi");
        }

        System.out.println("Stringa passata: " + UserInput);
    }

    public static void main(String[] args) {
        Security sec = new Security();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Inserisci la tua parola: ");
        String parola = scanner.nextLine();
        try {
            sec.InputValidation(parola);
        } catch (IllegalArgumentException e) {
            System.out.println("Quello che hai scritto non va bene");
        }
        sec.DbConnection();
        scanner.close();
    }
}