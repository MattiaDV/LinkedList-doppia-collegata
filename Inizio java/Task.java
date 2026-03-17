public class Task {
    private String title;
    private String desc;

    public Task(String title, String desc) {
        this.title = title;
        this.desc = desc;
    }

    @Override
    public String toString() {
        return "Title: " + title + "\nDesc: " + desc + "\n\n";
    }

    public String getTitle() {
        return title;
    }

    public String getDesc() {
        return desc;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }
}
