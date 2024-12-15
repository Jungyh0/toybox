package project;

import java.awt.Color;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

public class kiosk extends JFrame implements KeyListener{
	String[] text = {"한국어", "English", "日本語", "中国人"};
	JLabel word;
	static int index = 0;
	JRadioButton[] language;
	JPanel radio_panel, input;
	
	kiosk(){
		super("키오스크 프로그램");
		setSize(600,700);
	    setLocationRelativeTo(null);
	    setVisible(true);
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    setResizable(false);
	    addKeyListener((KeyListener) this);
	    input = new JPanel();	add(input,"Center");	input.setBackground(Color.cyan);
	    radio_panel = new JPanel();	add(radio_panel, "South");	radio_panel.setBackground(Color.white);
	    word = new JLabel("시작하려면 엔터를 누르세요.");	input.add(word);
	    
	    language = new JRadioButton[4];
	    ButtonGroup radio_group = new ButtonGroup();
	    for (int i = 0; i < language.length; i++) {
	    	if (i == 0) 
	    		language[i] = new JRadioButton(text[i],true);
	    	else 
	    		language[i] = new JRadioButton(text[i]);
	    	radio_group.add(language[i]);
	    	radio_panel.add(language[i]);
	    	language[i].addItemListener(new MyItemListener());
	    	language[i].addKeyListener((KeyListener) this);
	    	language[i].setBackground(Color.white);
	    }
	}
	
	class MyItemListener implements ItemListener {

		@Override
		public void itemStateChanged(ItemEvent e) {
            if(language[0].isSelected()) {
            	System.out.println("한국어");
            	index = 0;
            }
            
            else if(language[1].isSelected()) {
            	System.out.println("영어");
            	index = 1;
            }
            
            else if(language[2].isSelected()) {
            	System.out.println("일본어");
            	index = 2;
            }
            
            else if(language[3].isSelected()) {
            	System.out.println("중국어");
            	index = 3;
            }
			
		}

    }
	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_ENTER){
			setVisible(false);
			new order();
		}
	}
	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}

}
