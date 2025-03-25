/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package graphicUI;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.GroupLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.WindowConstants;
import model.card.Card;

/**
 *
 * @author Kostas Goumas
 */
public class View extends JFrame {

	private JLayeredPane player_cards[];
	private JLayeredPane player_safetyPile[];
	private JLayeredPane player_MilesPile[];
	private JLayeredPane player_BattlePile[];
	private JLayeredPane player_runPile[];
	private JLayeredPane fold_plesio;
	private JButton[] tempCard;
	Image image;
	private ImageExtention basic_panel;
	private JTextField  nea,message;
	private JTextField[] score;
	URL imageURL;
	ClassLoader cldr;

	public View() {
		cldr = this.getClass().getClassLoader();
		this.setResizable(false);
		this.setTitle("Mille Bornes Kostas Goumas");
		this.setPreferredSize(new Dimension(600,700));

	}
	public void removeAllFromBasicPanel(){
		this.basic_panel.removeAll();
	}
	public JLayeredPane getPlayerCards(int player) {
		return player_cards[player];
	}

	private void initPanels(JLayeredPane[] panel) {
		for (JLayeredPane pane : panel) {
			pane = new JLayeredPane();
		}

	}

	public void initComponents() {

		tempCard = new JButton[2];
		imageURL = cldr.getResource("resources/images/background.jpg");
		image = new ImageIcon(imageURL).getImage();
		basic_panel = new ImageExtention(image);
                
		player_cards = new JLayeredPane[2];
		player_safetyPile = new JLayeredPane[2];
		player_MilesPile = new JLayeredPane[2];
		player_runPile = new JLayeredPane[2];
		player_BattlePile = new JLayeredPane[2];
		player_cards[0] = new JLayeredPane();
		player_cards[1] = new JLayeredPane();
		player_safetyPile[0] = new JLayeredPane();
		player_safetyPile[1] = new JLayeredPane();
		player_MilesPile[0] = new JLayeredPane();
		player_MilesPile[1] = new JLayeredPane();
		player_runPile[0] = new JLayeredPane();
		player_runPile[1] = new JLayeredPane();
		player_BattlePile[0] = new JLayeredPane();
		player_BattlePile[1] = new JLayeredPane();

		fold_plesio = new JLayeredPane();

		message = new JTextField();
		nea = new JTextField();
		score=new JTextField[2];
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
//edw vazoume ta panel gia tous 2 paixtes opou kai tha fenontai ta score
                
		player_cards[1].setBounds(10, 70, 520, 105);
		basic_panel.add(player_cards[1], JLayeredPane.DEFAULT_LAYER);

		player_safetyPile[1].setBounds(10, 190, 280, 100);
		basic_panel.add(player_safetyPile[1], JLayeredPane.DEFAULT_LAYER);

		player_MilesPile[1].setBounds(300, 190, 70, 100);
		basic_panel.add(player_MilesPile[1], JLayeredPane.DEFAULT_LAYER);

		player_BattlePile[1].setBounds(380, 190, 70, 100);
		basic_panel.add(player_BattlePile[1], JLayeredPane.DEFAULT_LAYER);

		player_runPile[1].setBounds(460, 190, 70, 100);
		basic_panel.add(player_runPile[1], JLayeredPane.DEFAULT_LAYER);

		player_cards[0].setBounds(10, 530, 520, 105);
		basic_panel.add(player_cards[0], JLayeredPane.DEFAULT_LAYER);
                
		player_safetyPile[0].setBounds(10, 420, 280, 100);
		basic_panel.add(player_safetyPile[0], JLayeredPane.DEFAULT_LAYER);

		player_MilesPile[0].setBounds(300, 420, 70, 100);
		basic_panel.add(player_MilesPile[0], JLayeredPane.DEFAULT_LAYER);

		player_BattlePile[0].setBounds(380, 420, 70, 100);
		basic_panel.add(player_BattlePile[0], JLayeredPane.DEFAULT_LAYER);

		player_runPile[0].setBounds(460, 420, 70, 100);
		basic_panel.add(player_runPile[0], JLayeredPane.DEFAULT_LAYER);

		fold_plesio.setBounds(180, 300, 70, 100);
		basic_panel.add(fold_plesio, JLayeredPane.DEFAULT_LAYER);
                nea.setBounds(260, 300, 70, 100);
		basic_panel.add(nea, JLayeredPane.DEFAULT_LAYER);
		nea.setBackground(Color.white);

		
		nea.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.RED));
		nea.setEditable(false);
		nea.setText("Cards");
		score[1]=new JTextField();
		score[1].setBounds(200,2,150,50);
		basic_panel.add(score[1], JLayeredPane.DEFAULT_LAYER);
		score[1].setBackground(Color.cyan);
		score[1].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.cyan));
		score[1].setEditable(false);
		score[1].setText("Player 2:0 Miles");
		
		score[0]=new JTextField();
		score[0].setBounds(10,2,150,50);
		basic_panel.add(score[0], JLayeredPane.DEFAULT_LAYER);
		score[0].setBackground(Color.lightGray);
		score[0].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.lightGray));
		score[0].setEditable(false);
		score[0].setText("Player 1:0 Miles");
                
		

		GroupLayout layout = new GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
				layout.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addComponent(basic_panel, GroupLayout.PREFERRED_SIZE, 900, GroupLayout.PREFERRED_SIZE));
		layout.setVerticalGroup(
				layout.createParallelGroup(GroupLayout.Alignment.LEADING)
				.addComponent(basic_panel, GroupLayout.PREFERRED_SIZE, 680, GroupLayout.PREFERRED_SIZE));

		pack();

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		player_cards[0].setOpaque(true);
		player_cards[0].setBackground(Color.lightGray);
		player_safetyPile[0].setOpaque(false);
		player_safetyPile[0].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.lightGray));
		player_MilesPile[0].setOpaque(false);
		player_MilesPile[0].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.lightGray));
		player_runPile[0].setOpaque(false);
		player_runPile[0].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.lightGray));
		player_BattlePile[0].setOpaque(false);
		player_BattlePile[0].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.lightGray));

		fold_plesio.setOpaque(false);
		fold_plesio.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.red));
		player_cards[1].setOpaque(true);
		player_cards[1].setBackground(Color.cyan);
		player_safetyPile[1].setOpaque(false);
		player_safetyPile[1].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.cyan));
		player_MilesPile[1].setOpaque(false);
		player_MilesPile[1].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.cyan));
		player_runPile[1].setOpaque(false);
		player_runPile[1].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.cyan));
		player_BattlePile[1].setOpaque(false);
		player_BattlePile[1].setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.cyan));

		this.setLabel("Safety", Color.lightGray,this.player_safetyPile[0]);
		this.setLabel("Miles", Color.lightGray,this.player_MilesPile[0]);
		this.setLabel("Run", Color.lightGray,this.player_runPile[0]);
		this.setLabel("Battle", Color.lightGray,this.player_BattlePile[0]);
		this.setLabel("Safety", Color.cyan,this.player_safetyPile[1]);
		this.setLabel("Miles", Color.cyan,this.player_MilesPile[1]);
		this.setLabel("Run", Color.cyan,this.player_runPile[1]);
		this.setLabel("Battle", Color.cyan,this.player_BattlePile[1]);
		this.setLabel("Fold", Color.red, fold_plesio);
		Graphics g1 = basic_panel.getGraphics();
		basic_panel.paintComponent(g1);
		basic_panel.repaint();
	}

	
	public void setLabel(String type,Color c,JLayeredPane pane){
		JLabel label2 = new JLabel("<html>"+type+"<br>Stack</html>", JLabel.CENTER);
		label2.setForeground(c);
		label2.setBounds(0,0,50,50);
		label2.setVisible(true);
		pane.add(label2, JLayeredPane.DEFAULT_LAYER);
	}
	public void repaintPanel() {
		this.basic_panel.repaint();
	}

	public void setScore(int player, int score_input) {
		score[player].setText("Player "+(player+1)+ ": "+ score_input+" Miles");
	}
	

	public void setScore(int cards) {
		nea.setText("Cards:" + cards);
	}

	public ArrayList<JButton> setCards(int playerID, HashMap<Integer, Card> cards) {
		int x = 0, y = 0;
		ArrayList<JButton> buttons = new ArrayList<JButton>();
		for (Map.Entry<Integer, Card> card : cards.entrySet()) {
			JButton b = new JButton();
			b.setBounds(x, y, 70, 100);

			b.setName(card.getKey().toString());
			Image img;

			imageURL = cldr.getResource("resources/images/" + card.getValue() + ".jpg");
			image = new ImageIcon(imageURL).getImage();
			image = image.getScaledInstance(70, 100, java.awt.Image.SCALE_SMOOTH);
			b.setIcon(new ImageIcon(image));

			this.player_cards[playerID].add(b);
			buttons.add(b);
			x += 75;
		}
		basic_panel.repaint();
		return buttons;
	}

	public void addToFoldPile(JButton b) {
		this.fold_plesio.removeAll();
		b.setBounds(0, 0, 70, 100);
		b.setEnabled(false);
		this.fold_plesio.add(b);
	}

	public JButton addCardToPlayerPane(int playerID, Card card, int id) {
		int x = 6 * 75, y = 0;
		JButton button = new JButton();

		JButton b = new JButton();
		b.setBounds(x, y, 70, 100);

		b.setName(Integer.toString(id));
		
		Image img;

		imageURL = cldr.getResource("resources/images/" + card.toString() + ".jpg");
		image = new ImageIcon(imageURL).getImage();
		image = image.getScaledInstance(70, 100, java.awt.Image.SCALE_SMOOTH);
		b.setIcon(new ImageIcon(image));

		this.player_cards[playerID].add(b);
		tempCard[playerID] = b;
		basic_panel.repaint();
		return b;
	}

	public void replaceCard(int playerID, int x, int y) {
		tempCard[playerID].setBounds(x, y, 70, 100);
	}

	public void addToSafetyPile(int playerID, JButton b, int numOfCards) {
		b.setBounds(numOfCards * 70, 0, 70, 100);
		// b.setEnabled(false);
		this.player_safetyPile[playerID].add(b);
	}

	public void addToMilesPile(int playerID, JButton b) {
		this.player_MilesPile[playerID].removeAll();
		b.setBounds(0, 0, 70, 100);
		//b.setEnabled(false);
		this.player_MilesPile[playerID].add(b);
	}

	public void addTorunPile(int playerID, JButton b) {
		this.player_runPile[playerID].removeAll();
		b.setBounds(0, 0, 70, 100);
		//b.setEnabled(false);
		this.player_runPile[playerID].add(b);
	}

	public void addToBattlePile(int playerID, JButton b) {
		this.player_BattlePile[playerID].removeAll();
		b.setBounds(0, 0, 70, 100);
		//b.setEnabled(false);
		this.player_BattlePile[playerID].add(b);
	}
	
	public void removeAllFromBattlePile(int playerID){
		this.player_BattlePile[playerID].removeAll();
	}

	public void removeAllFromRunPile(int turn) {
		this.player_runPile[turn].removeAll();
	}
}
