/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainPackage;

import controller.Controller;
import graphicUI.View;

/**
 *
 * @author Kostas Goumas
 */
public class MainClass {
    public static void main(String[] args) {           

         View view = new View();
	 view.setVisible(true);
         Controller controller = new Controller(view);
         
}
}
