import java.util.ArrayList;

public class User {
    private String completename;
    private String username;
    private String email;
    private int eta;
    private String password;
    private ArrayList<Task> tasks;

    public User(String completename, String username, String email, int eta, String password) {
        this.completename = completename;
        this.username = username;
        this.email = email;
        this.eta = eta;
        this.password = password;
        this.tasks = new ArrayList<>();
    }

    @Override
    public String toString() {
        return "Complete name: " + completename + "\nUsername: " + username + "\nEmail: " + email + "\nEta: " + eta + "\nTasks: " + tasks + "\n\n";
    }

    public void addTask(Task new_task) {
        tasks.add(new_task);
    }

    public ArrayList<Task> getTasks() {
        return tasks;
    }

    public String getCompletename() {
        return completename;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public int getEta() {
        return eta;
    }

    public String getPassword() {
        return password;
    }

    public void setCompletename(String completename) {
        this.completename = completename;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setEta(int eta) {
        this.eta = eta;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}