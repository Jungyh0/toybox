package project;

import java.awt.FlowLayout;

import javax.swing.*;

public class burger_page extends JPanel{
	JScrollPane scrollPane;
	JPanel pane1;
	JButton but1, but2, but3, but4, but5;
	burger_page(){
		/*setSize(600,700);
	    setLocationRelativeTo(null);
	    setVisible(true);
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    setResizable(false);*/
		/*scrollPane = new JScrollPane(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		scrollPane.setBounds(4, 4, 340, 330);*/
		//add(scrollPane, "East");
		pane1 = new JPanel();	pane1.setLayout(new FlowLayout());	add(pane1,"Center");
		but1 = new JButton("tset1");	pane1.add(but1);
		but2 = new JButton("tset2");	pane1.add(but2);
		but3 = new JButton("tset3");	pane1.add(but3);
		but4 = new JButton("tset4");	pane1.add(but4);
		but5 = new JButton("tset5");	pane1.add(but5);
		
	}
	public static void main(String[] args) {
		new burger_page();
	}
}
