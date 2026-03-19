interface Dog {
    void saluta();
    void abbaia();
    abstract void draw();
}

abstract class Lol {
    public void message() {
        System.out.println("Ciao mondo");
    }
}

public class Animal implements Dog {
    public void draw() {
        System.out.println("Disegno");
    }

    public void saluta() {
        System.out.println("Ciao sono un cane");
    }

    public void abbaia() {
        System.out.println("Bau");
    }

    public static void main(String args[]) {
        Animal a = new Animal();
        a.abbaia();
        a.saluta();
    }
}
