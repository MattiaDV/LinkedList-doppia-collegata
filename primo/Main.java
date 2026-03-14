package primo;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Font;

import java.awt.BorderLayout;
import java.awt.GridLayout;

public class Main {
    private static JButton creaBottone(String testo, JLabel label) {
        JButton btn = new JButton(testo);
        btn.addActionListener(e -> {
            label.setText(label.getText() + testo);
        });
        return btn;
    }
    public static void main(String args[]) {
        JFrame frame = new JFrame("Calcolatrice");
        frame.setSize(300, 400);
        JLabel label = new JLabel("");
        label.setFont(new Font("Arial", Font.PLAIN, 32));
        label.setHorizontalAlignment(JLabel.RIGHT);
        frame.add(label, BorderLayout.NORTH);
        JPanel panel = new JPanel(new GridLayout(4, 4));
        frame.add(panel, BorderLayout.CENTER);
        panel.add(creaBottone("1", label));
        panel.add(creaBottone("2", label));
        panel.add(creaBottone("3", label));
        panel.add(creaBottone("4", label));
        panel.add(creaBottone("5", label));
        panel.add(creaBottone("6", label));
        panel.add(creaBottone("7", label));
        panel.add(creaBottone("8", label));
        panel.add(creaBottone("9", label));
        panel.add(creaBottone("0", label));
        panel.add(creaBottone("+", label));
        panel.add(creaBottone("-", label));
        panel.add(creaBottone("*", label));
        panel.add(creaBottone("/", label));
        JButton clear = new JButton("C");
        clear.addActionListener(e -> {
            label.setText("");
        });
        panel.add(clear);
        JButton uguale = new JButton("=");
        uguale.addActionListener(e -> {
            String s = label.getText();
            if (s.contains("+")) {
                String parti[] = s.split("\\+");
                float n1 = Float.parseFloat(parti[0]);
                float n2 = Float.parseFloat(parti[1]);
                float res = n1 + n2;
                String ris = "" + res;
                label.setText(ris);
            } else if (s.contains("/")) {
                String parti[] = s.split("\\/");
                float n1 = Float.parseFloat(parti[0]);
                float n2 = Float.parseFloat(parti[1]);
                float res = (float) n1 / n2;
                String ris = "" + res;
                label.setText(ris);
            } else if (s.contains("*")) {
                String parti[] = s.split("\\*");
                float n1 = Float.parseFloat(parti[0]);
                float n2 = Float.parseFloat(parti[1]);
                float res = n1 * n2;
                String ris = "" + res;
                label.setText(ris);
            } else if (s.contains("-")) {
                String parti[] = s.split("\\-");
                float n1 = Float.parseFloat(parti[0]);
                float n2 = Float.parseFloat(parti[1]);
                float res = n1 - n2;
                String ris = "" + res;
                label.setText(ris);
            }
        });
        panel.add(uguale);

        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
