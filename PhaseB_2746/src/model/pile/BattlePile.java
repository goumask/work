/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model.pile;

import javax.swing.JOptionPane;
import model.player.Player;
import model.card.Card;
import model.card.HazardCard;
import model.card.HazardCardEnumType;
import model.card.RemedyCard;
import model.card.RemedyCardEnumType;
import model.card.SafetyCardEnumType;

/**
 *
 * @author Kostas Goumas
 */
public class BattlePile {

	Card card;
	private boolean hasPlayedRoll;


	public Card getLastCard() {
		return card;
	}

	public void setCard(Card crd) {
		this.card = crd;

	}

	public boolean hasPlayedRollCard() {
		return hasPlayedRoll;
	}


	public void setHasPlayedRoll(boolean hasPlayedRoll) {
		this.hasPlayedRoll = hasPlayedRoll;
	}

	public boolean addHazardToBattlePile(Player player, Card cardnum) {
		if (this.hasPlayedRoll == false && !player.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {
                    JOptionPane.showMessageDialog (null, "Roll Card Has not been played yet", "Error", JOptionPane.INFORMATION_MESSAGE);
			
			return false;
		}

		HazardCard haz = (HazardCard) cardnum;
		if (haz.getHazardEnum().equals(HazardCardEnumType.ACCIDENT)) {
			if (player.getSafetyPile().containsCard(SafetyCardEnumType.DRIVING_ACE)) {
                            JOptionPane.showMessageDialog (null, "Driving Ace Safety Card protects from playing this card", "Error", JOptionPane.INFORMATION_MESSAGE);
				
				return false;
			}
			this.card = cardnum;
			return true;
		}
		if (haz.getHazardEnum().equals(HazardCardEnumType.FLAT_TIRE)) {
			if (player.getSafetyPile().containsCard(SafetyCardEnumType.PUNCTURE_PROOF)) {
                            JOptionPane.showMessageDialog (null, "Puncture Proof Safety Card protects from playing this card", "Error", JOptionPane.INFORMATION_MESSAGE);
				
				return false;
			}
			this.card = cardnum;
			return true;
		}
		if (haz.getHazardEnum().equals(HazardCardEnumType.OUT_OF_GAS)) {
			if (player.getSafetyPile().containsCard(SafetyCardEnumType.EXTRA_TANK)) {
                            JOptionPane.showMessageDialog (null, "Extra Tank Safety Card protects from playing this card", "Error", JOptionPane.INFORMATION_MESSAGE);
	
				return false;
			}
			this.card = cardnum;
			return true;
		}
		if (haz.getHazardEnum().equals(HazardCardEnumType.STOP)) {
			if (player.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {
                            JOptionPane.showMessageDialog (null, "Right of way Safety Card protects from playing this card", "Error", JOptionPane.INFORMATION_MESSAGE);

				return false;
			}
			this.card = cardnum;
			return true;
		}
		return false;
	}

	public boolean addRemedyToBattlePile(Player p, Card c) {
		RemedyCard haz = (RemedyCard) c;
		if (haz.getRemedyCardEnum().equals(RemedyCardEnumType.ROLL)) {
			if (p.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {
                            JOptionPane.showMessageDialog (null, "Right of way Safety Card Exists- No need for Roll", "Error", JOptionPane.INFORMATION_MESSAGE);

				return false;
			}
			if (this.getLastCard() == null) {
				this.setHasPlayedRoll(true);
				this.card = c;
				return true;
			}
			if (this.getLastCard().getType().equals("Remedy")) {
				RemedyCard hc2 = (RemedyCard) this.getLastCard();
				if (!hc2.getRemedyCardEnum().equals(RemedyCardEnumType.ROLL)) {
					this.card = c;
					return true;
				}
			}
		}
		if (this.hasPlayedRoll == false && !p.getSafetyPile().containsCard(SafetyCardEnumType.RIGHT_OF_WAY)) {

			JOptionPane.showMessageDialog (null, "Roll Card Has not been played", "Error", JOptionPane.INFORMATION_MESSAGE);
                        return false;
		}
		if (this.getLastCard() != null && this.getLastCard().getType().equals("Remedy")) {

			JOptionPane.showMessageDialog (null, "Last Card in this Stack is Remedy Card", "Error", JOptionPane.INFORMATION_MESSAGE);
                        return false;
		}

		if (haz.getRemedyCardEnum().equals(RemedyCardEnumType.GASOLINE) && this.getLastCard().toString().equals(HazardCardEnumType.OUT_OF_GAS.toString())) {
			this.card = c;
			return true;
		}
		if (haz.getRemedyCardEnum().equals(RemedyCardEnumType.REPAIR) && this.getLastCard().toString().equals(HazardCardEnumType.ACCIDENT.toString())) {
			this.card = c;
			return true;
		}
		if (haz.getRemedyCardEnum().equals(RemedyCardEnumType.SPARE_TIRE) && this.getLastCard().toString().equals(HazardCardEnumType.FLAT_TIRE.toString())) {
			this.card = c;
			return true;
		}
		if (haz.getRemedyCardEnum().equals(RemedyCardEnumType.ROLL) && this.getLastCard().toString().equals(HazardCardEnumType.STOP.toString())) {
			this.card = c;
			return true;
		}
                JOptionPane.showMessageDialog (null, "Remedy Card doesn't match with  Hazard Card", "Error", JOptionPane.INFORMATION_MESSAGE);

		return false;
	}
}
