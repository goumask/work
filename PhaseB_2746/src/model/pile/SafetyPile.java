/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model.pile;

import java.util.ArrayList;
import model.card.Card;
import model.card.HazardCard;
import model.card.HazardCardEnumType;
import model.card.SafetyCardEnumType;

/**
 *
 * @author Kostas Goumas
 */
public class SafetyPile {
    private int numberOfCards;
    public ArrayList<SafetyCardEnumType> sftList;
    private ArrayList<Card> cards;
    
    public SafetyPile(){
        sftList=new ArrayList<>();
    }
	public int getNumberOfCards(){
            return numberOfCards;
        }
        
        public void addCard(SafetyCardEnumType en){
            this.sftList.add(en);
            this.numberOfCards++;
        }
        
        public boolean containsCard(SafetyCardEnumType en){
            return sftList.contains(en);
        }
        

		
	public boolean Match(Card c){
			if (c.getType().equals("Hazard")){
				HazardCard haz=(HazardCard ) c;
				if (haz.getHazardEnum().equals(HazardCardEnumType.SPEED_LIMIT) && this.containsCard(SafetyCardEnumType.RIGHT_OF_WAY))
					return true;
                                if (haz.getHazardEnum().equals(HazardCardEnumType.ACCIDENT) && this.containsCard(SafetyCardEnumType.DRIVING_ACE))
					return true;
				if (haz.getHazardEnum().equals(HazardCardEnumType.FLAT_TIRE) && this.containsCard(SafetyCardEnumType.PUNCTURE_PROOF))
					return true;
				if (haz.getHazardEnum().equals(HazardCardEnumType.OUT_OF_GAS) && this.containsCard(SafetyCardEnumType.EXTRA_TANK))
					return true;
			}
			return false;
	}
}
