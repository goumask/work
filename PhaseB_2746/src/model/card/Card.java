/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model.card;

/**
 * @author Kostas Goumas
 */
public interface Card {


	public int getValue();
        

	public void setValue(int value);


	public int getPoints();


	public void setPoints(int points);

	@Override
	public String toString();
        
        public String getType();

	
}
