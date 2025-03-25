/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package graphicUI;

import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JLayeredPane;

/**
 *
 * @author Kostas Goumas
 */
public class ImageExtention extends JLayeredPane {

      Image image;

        public ImageExtention(Image img) {
            image=img;
        }

        @Override
        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(image, 0, 0, this);
        }
    }