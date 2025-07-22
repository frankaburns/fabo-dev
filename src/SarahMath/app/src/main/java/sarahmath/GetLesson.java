

package sarahmath;
import java.awt.GridLayout;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class GetLesson {

    public Map<String, Integer> getLesson() {
        Map<String, Integer> lesson = new HashMap<>();

        JTextField levelField = new JTextField(10);
        JTextField randomField = new JTextField(3);
        JTextField functionField = new JTextField(10);
        JTextField problemsField = new JTextField(4);

        JPanel panel = new JPanel(new GridLayout(0, 1));
        panel.add(new JLabel("Level(0: 1-diget,1: 2-diget, 2: 3-diget):"));
        mainBinding.textViewHistory.setText("Level(0: 1-diget,1: 2-diget, 2: 3-diget):");

        String result = sharedPreferences.getString("result","");
        panel.add(levelField);
        panel.add(new JLabel("Random(1-yes, 0-ordered):"));
        panel.add(randomField);
        panel.add(new JLabel("Function(0-add, 1-subtract, 2-multiply, 3-divide):"));
        panel.add(functionField);
        panel.add(new JLabel("Number of problems"));
        panel.add(problemsField);
        int result = JOptionPane.showConfirmDialog(null, panel, "Enter Information",
                JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

        if (result == JOptionPane.OK_OPTION) {
            String level = levelField.getText();
            String random = randomField.getText();
            String function = functionField.getText();
            String problems = problemsField.getText();

            lesson.put("level", Integer.parseInt(level));
            lesson.put("random", Integer.parseInt(random));
            lesson.put("function", Integer.parseInt(function));
            lesson.put("problems", Integer.parseInt(problems));
        } else {
            System.out.println("Cancelled");
            lesson.put("Cancelled", Integer.parseInt("9999"));
        }
        return lesson;
    }
}
