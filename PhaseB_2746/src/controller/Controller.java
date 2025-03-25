/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import graphicUI.View;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.net.URL;
import java.util.ArrayList;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;
import model.card.Card;
import model.card.HazardCard;
import model.card.HazardCardEnumType;
import model.card.RemedyCard;
import model.card.RemedyCardEnumType;
import model.card.SafetyCard;
import model.pile.DeckofGame;
import model.player.Player;

/**
 *
 * @author Kostas Goumas
 */
public class Controller {
        private View view; 
	private DeckofGame deck;
	private Player[] players;
	private int turn = 0;

	public Controller(View view) {
		this.view = view;
		this.view.initComponents();
		players = new Player[2];
		players[0] = new Player("Kwstas1", 0);
		players[1] = new Player("Kwstas2", 1);
		deck = new DeckofGame();
		deck.createCards();
		deck.shuffleCards();
		players[0].setPlayerCards(deck.getCards());
		players[1].setPlayerCards(deck.getCards());
		
                setButtons();
		players[0].setTurn(true);
		players[1].setTurn(false);
		addCard();

	}

	public void setButtons() {
		ArrayList<JButton> buttons1 = view.setCards(0, players[0].getPlayerCards());
		for (JButton but : buttons1) {
			but.addMouseListener(new CardListener());
		}
                ArrayList<JButton> buttons2 = view.setCards(1, players[1].getPlayerCards());
		for (JButton but : buttons2) {
			but.addMouseListener(new CardListener());
		}
	}

	public int changeTurn(int Turn) {
		if (Turn == 0) {
			return 1;
		} else {
			return 0;
		}
	}

	private void addCard() {
		Card card = deck.getNextCard();
		int id = deck.getNextCardID();
		view.addCardToPlayerPane(turn, card, id).addMouseListener(new CardListener());
		players[turn].getPlayerCards().put(id, card);
		view.setScore(deck.getIds());
	}

	private class CardListener implements MouseListener {

		@Override
		public void mouseClicked(MouseEvent e) {
			boolean MoveISacceptedasValid = false;
			JButton but = ((JButton) e.getSource());
                        int x_mouse_coordinates = but.getX();
                        int y_mouse_coordinates = but.getY();
			boolean isSafety = false;
			if (players[turn].getPlayerCards().containsKey(Integer.parseInt(but.getName()))) {
                            //otan paththei to dexi koumpi stenlei tin karta stin stoiva aporipsis
				if (SwingUtilities.isRightMouseButton(e)) {
					players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));

					view.getPlayerCards(turn).remove(but);
					view.addToFoldPile(but);
					view.repaint();
					MoveISacceptedasValid = true;
				} else if (SwingUtilities.isLeftMouseButton(e)) {
					Card card = players[turn].getPlayerCards().get(Integer.parseInt(but.getName()));
					if (null != card.getType()) {
						switch (card.getType()) {
							case "Miles":
								
								if (players[turn].getMilesPile().checkIfCanPlay(players[turn], Integer.parseInt(but.getName()))) {
									view.getPlayerCards(turn).remove(but);
									view.addToMilesPile(turn, but);
									view.setScore(turn, players[turn].getMilesPile().getMilesPoints());
									view.repaint();
									MoveISacceptedasValid = true;
								} 
								break;
							case "Safety":
								SafetyCard safetycard = (SafetyCard) card;
								players[turn].getSafetyPile().addCard(safetycard.getSafetyCardEnum());
								players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));
								view.getPlayerCards(turn).remove(but);

								view.addToSafetyPile(turn, but, players[turn].getSafetyPile().getNumberOfCards() - 1);
								if (players[turn].getRunPile().getLastCard() != null && players[turn].getSafetyPile().Match(players[turn].getRunPile().getLastCard())) {
									view.removeAllFromRunPile(turn);
									players[turn].getRunPile().removeCard();
								}
                                                                else if (players[turn].getBattlePile().getLastCard() != null && players[turn].getSafetyPile().Match(players[turn].getBattlePile().getLastCard())) {
									view.removeAllFromBattlePile(turn);
									players[turn].getBattlePile().setCard(null);
								}
								view.repaint();
								MoveISacceptedasValid = true;
								isSafety = true;
								break;
							case "Remedy":
								RemedyCard remedycard = (RemedyCard) card;
								if (remedycard.getRemedyCardEnum().equals(RemedyCardEnumType.END_OF_LIMIT)) {
									if (players[turn].getRunPile().addToRunPile(players[turn], remedycard)) {
										players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));
										view.getPlayerCards(turn).remove(but);
										view.addTorunPile(turn, but);
										view.repaint();
										MoveISacceptedasValid = true;
									}
								} else if (players[turn].getBattlePile().addRemedyToBattlePile(players[turn], remedycard)) {
									players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));
									view.getPlayerCards(turn).remove(but);
									view.addToBattlePile(turn, but);
									view.repaint();
									MoveISacceptedasValid = true;
								}
								
								break;
							case "Hazard":
								HazardCard hazardcard = (HazardCard) card;
								if (hazardcard.getHazardEnum().equals(HazardCardEnumType.SPEED_LIMIT)) {
									if (players[changeTurn(turn)].getRunPile().opponentAddToRunPile(players[changeTurn(turn)], hazardcard)) {
										players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));
										view.getPlayerCards(turn).remove(but);
										view.addTorunPile(changeTurn(turn), but);
										view.repaint();
										MoveISacceptedasValid = true;
									}
								} else {
									if (players[changeTurn(turn)].getBattlePile().addHazardToBattlePile(players[changeTurn(turn)], hazardcard)) {
										players[turn].getPlayerCards().remove(Integer.parseInt(but.getName()));
										view.getPlayerCards(turn).remove(but);
										view.addToBattlePile(changeTurn(turn), but);
										view.repaint();
										MoveISacceptedasValid = true;
									} 
								}
								break;
						}
					}

				}
			}

			if (players[turn].isWinner()) {

				JOptionPane.showMessageDialog(null, "Player:" + (turn + 1) + " Wins!!!!", "Winner", JOptionPane.INFORMATION_MESSAGE);
				view.removeAllFromBasicPanel();
				view.repaint();
				
			}
			if (MoveISacceptedasValid) {
				//kanoume replace tin karta pou patithike
				
				view.replaceCard(turn, x_mouse_coordinates, y_mouse_coordinates);
				
				
				if (isSafety == false) {
					turn = changeTurn(turn);
				}
				if (deck.getIds() != 0) {
					addCard();
				} else if (players[0].getPlayerCards().isEmpty() && players[1].getPlayerCards().isEmpty()) {
					if (players[0].getMilesPile().getMilesPoints() > players[1].getMilesPile().getMilesPoints()) {
						JOptionPane.showMessageDialog(null, "Player:1 " + " Wins!!!!", "Winner", JOptionPane.INFORMATION_MESSAGE);
					} else if (players[0].getMilesPile().getMilesPoints() < players[1].getMilesPile().getMilesPoints()) {
						JOptionPane.showMessageDialog(null, "Player:2 " + " Wins!!!!", "Winner", JOptionPane.INFORMATION_MESSAGE);
					} else {
						if (players[0].getMilesPile().getMilesPoints() > players[1].getMilesPile().getMilesPoints()) {
							JOptionPane.showMessageDialog(null, "Draw", "Draw", JOptionPane.INFORMATION_MESSAGE);
						}
					}
					view.removeAllFromBasicPanel();
					view.repaint();
					
				}
                                playSound("accept.wav");
			} 

		}//telos mouseclicked

		@Override
		public void mousePressed(MouseEvent e) {
			
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			
		}

		@Override
		public void mouseEntered(MouseEvent e) {
			
		}

		@Override
		public void mouseExited(MouseEvent e) {
			
		}
	}

	public void playSound(String soundName) {
		try {
			URL ur = this.getClass().getClassLoader().getResource("sounds/" + soundName);
			AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(ur);
			Clip clip = AudioSystem.getClip();
			clip.open(audioInputStream);
			clip.start();
		} catch (Exception ex) {
			
		}
	}
}
