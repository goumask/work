/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model.pile;

import model.card.Card;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Random;
import model.card.HazardCard;
import model.card.HazardCardEnumType;
import model.card.MilesCard;
import model.card.RemedyCard;
import model.card.RemedyCardEnumType;
import model.card.SafetyCard;
import model.card.SafetyCardEnumType;

/**
 *
 * @author Kostas Goumas
 */
public class DeckofGame {

	private Card[][] playerCards;
	private HashMap<Integer, Card> drawPileCards;
	private ArrayList<Integer> ids;
	private Card nextCard;
	private int id = 0;
	private ArrayList<String> cardsImage;

    public Integer getIds() {
        return ids.size();
    }

	public void createMilesCards() {
		int miles = 25;
		for (int i = 0; i < 46; i++) {
			drawPileCards.put(id, new MilesCard(miles));
			ids.add(id++);

			if (i != 0 && i % 10 == 0 && i < 40) {
				miles += 25;
			}
			if (i == 41) {
				miles *= 2;
			}
		}
	}

	public void createSafetyCards() {
		for (SafetyCardEnumType enumCard : SafetyCardEnumType.values()) {
			drawPileCards.put(id, new SafetyCard(enumCard));
			ids.add(id++);

		}

	}

	public void createRemedyCards() {
		for (RemedyCardEnumType enumCard : RemedyCardEnumType.values()) {
			
			if (enumCard == RemedyCardEnumType.ROLL) {
				for (int i = 0; i < 14; i++) {
				drawPileCards.put(id, new RemedyCard(enumCard));
				ids.add(id++);
                            }
			}
                        else
                        {
                            for (int i = 0; i < 6; i++) {
				drawPileCards.put(id, new RemedyCard(enumCard));
				ids.add(id++);
                            }
                        }
			

		}

	}

	public void createHazardCards() {
		for (HazardCardEnumType enumCard : HazardCardEnumType.values()) {
			
			if (enumCard == HazardCardEnumType.SPEED_LIMIT) {
				
                                for (int i = 0; i < 4; i++) {
				drawPileCards.put(id, new HazardCard(enumCard));
				ids.add(id++);
                                }
			}
                        else if (enumCard == HazardCardEnumType.STOP) {
				for (int i = 0; i < 5; i++) {
				drawPileCards.put(id, new HazardCard(enumCard));
				ids.add(id++);
                                }
			}
                        else
                        {
                            for (int i = 0; i < 3; i++) {
				drawPileCards.put(id, new HazardCard(enumCard));
				ids.add(id++);
                                }
                        }
			

		}

	}

	public Card getNextCard() {
                if (!ids.isEmpty())
                    return drawPileCards.get(ids.get(0));
                else
                    return null;
	}
        public int getNextCardID(){
            if (ids.isEmpty())
                return -1;
            int cardID=ids.get(0);
            ids.remove(0);
            return cardID;
        }
	public void createCards() {
		drawPileCards = new HashMap<>();
		ids = new ArrayList<>();
		this.createMilesCards();
		this.createSafetyCards();
		this.createRemedyCards();
		this.createHazardCards();
		
	}

	public void shuffleCards() {
		long seed = System.nanoTime();
		Collections.shuffle(ids, new Random(seed));
	}

	public HashMap<Integer,Card> getCards() {
		HashMap<Integer,Card> cards = new HashMap<>();
		for (int i = 0; i < 6; i++) {
			cards.put(ids.get(0),this.getNextCard());
			ids.remove(0);
		}
		return cards;
	}
}
