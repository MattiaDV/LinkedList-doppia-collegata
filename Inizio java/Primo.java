import java.util.Scanner;

public class Primo {

    public static User createUser(Scanner scanner) {
        System.out.println("Inserire nome completo: ");
        String complete = scanner.nextLine();
        System.out.println("Inserire username: ");
        String username = scanner.nextLine();
        System.out.println("Inserire email: ");
        String email = scanner.nextLine();
        System.out.println("Inserire eta: ");
        int eta = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Inserire password: ");
        String pasw = scanner.nextLine();

        User new_user = new User(complete, username, email, eta, pasw);
        return new_user;
    }

    public static void createTask(Scanner scanner, User people) {
        System.out.println("Inserire titolo task: ");
        String titolo = scanner.nextLine();
        System.out.println("Inserire descrizione task: ");
        String desc = scanner.nextLine();
        Task new_task = new Task(titolo, desc);
        people.addTask(new_task);
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        User new_u = createUser(scanner);
        createTask(scanner, new_u);
        createTask(scanner, new_u);
        System.out.println("\n\n");
        System.out.println(new_u);
        scanner.close();
    }
}
