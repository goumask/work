/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model.pile;

import javax.swing.JOptionPane;
import model.player.Player;
import model.card.Card;
import model.card.HazardCardEnumType;
import model.card.MilesCard;
import model.card.RemedyCardEnumType;
import model.card.SafetyCardEnumType;

/**
 *
 * @author Kostas Goumas
 */
public class MilesPile {

	private boolean canPlay;
	private int milesPoints = 0;
	private int numberof200;


	public boolean canPlay() {
		return this.canPlay;
	}

	public void setCanPlay(boolean iscapableofplaying) {
		this.canPlay = iscapableofplaying;
	}

	public void milesPoints(int points) {
		milesPoints += points;
	}

	public boolean checkIfCanPlay(Player player, int cardnum) {

		if ((player.getBattlePile().getLastCard() != null && player.getBattlePile().getLastCard().toString().equals(RemedyCardEnumType.ROLL.toString())) || player.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {

			MilesCard mc = (MilesCard) player.getPlayerCards().get(cardnum);
			if (player.getRunPile().getLastCard() != null && player.getRunPile().getLastCard().toString().equals(HazardCardEnumType.SPEED_LIMIT.toString())) {
				
				if (mc.getMiles() > 50) {
                                        JOptionPane.showMessageDialog (null, "Speed Limit", "Error", JOptionPane.INFORMATION_MESSAGE);
					
					return false;
				} else if (mc.getMiles() + this.milesPoints > 1000) {
                                        JOptionPane.showMessageDialog (null, "Miles cannot become over 1000", "Error", JOptionPane.INFORMATION_MESSAGE);
					
					return false;
				} else {
					this.milesPoints(mc.getMiles());
					player.getPlayerCards().remove(cardnum);
					return true;
				}

			}
			else if ( player.getBattlePile().getLastCard() != null && player.getBattlePile().getLastCard().getType().equals("Hazard")){
				
                                JOptionPane.showMessageDialog (null, "Hazard Card Exists", "Error", JOptionPane.INFORMATION_MESSAGE);
				return false;
			}
			else if ((mc.getMiles() + this.milesPoints) <= 1000) {
				if (mc.getMiles() == 200) {
					if (this.numberof200 == 2) {
                                                JOptionPane.showMessageDialog (null, "You have already played two cards of 200 Miles", "Error", JOptionPane.INFORMATION_MESSAGE);
						
						return false;
					} else {
						this.numberof200++;
					}
				}

				this.milesPoints(mc.getMiles());
				player.getPlayerCards().remove(cardnum);
				if (this.milesPoints == 1000) {
					player.setIsWinner(true);
				}

				return true;
			}

		}
                JOptionPane.showMessageDialog (null, "Roll or Right of Way Card doesn't exist", "Error", JOptionPane.INFORMATION_MESSAGE);
		
		return false;
	}

	public int getMilesPoints() {
		return milesPoints;
	}
}
