import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.awt.image.*;

public class UserInterface implements ActionListener
{
    public GameEngine engine;
    private JFrame myFrame;
    public JTextField entryField;
    private JTextArea log;
    private JLabel image, solde, bag, life, keys, strength, crew;
    private JPanel panel;
    private GridBagConstraints gbc;
    private JButton north, northEast, northWest, east, west, southEast, southWest, south, look, help, back, none;
    private JButton chargeBeam, fireBeam;
    

    /**
     * Construct a UserInterface. As a parameter, a Game Engine
     * (an object processing and executing the game commands) is
     * needed.
     * 
     * @param gameEngine  The GameEngine object implementing the game logic.
     */
    public UserInterface(GameEngine gameEngine)
    {
        engine = gameEngine;
        createGUI();
    }

    /**
     * Print out some text into the text area.
     */
    public void print(String text)
    {
        log.append(text);
        log.setCaretPosition(log.getDocument().getLength());
    }

    /**
     * Print out some text into the text area, followed by a line break.
     */
    public void println(String text)
    {
        log.append(text + "\n");
        log.setCaretPosition(log.getDocument().getLength());
    }

    /**
     * Show an image file in the interface.
     */
    public void showImage(String imageName)
    {
        URL imageURL = this.getClass().getClassLoader().getResource(imageName);
        if(imageURL == null)
            System.out.println("image not found");
        else {
            ImageIcon icon = new ImageIcon(new ImageIcon(imageURL).getImage().getScaledInstance(600, 400, Image.SCALE_DEFAULT));
            image.setIcon(icon);
            myFrame.pack();
        }
    }

    /**
     * Enable or disable input in the input field.
     */
    public void enable(boolean on)
    {
        entryField.setEditable(on);
        if(!on)
            entryField.getCaret().setBlinkRate(0);
    }

    /**
     * Set up graphical user interface.
     */
    private void createGUI()
    {   /*
        myFrame = new JFrame("Hardes Game");
        entryField = new JTextField(34);

        log = new JTextArea();
        log.setEditable(false);
        JScrollPane listScroller = new JScrollPane(log);
        listScroller.setPreferredSize(new Dimension(200, 200));
        listScroller.setMinimumSize(new Dimension(100,100));

        JPanel panel = new JPanel();
        image = new JLabel();

        panel.setLayout(new BorderLayout());
        panel.add(image, BorderLayout.NORTH);
        panel.add(listScroller, BorderLayout.CENTER);
        panel.add(entryField, BorderLayout.SOUTH);

        myFrame.getContentPane().add(panel, BorderLayout.CENTER);

        // add some event listeners to some components
        myFrame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {System.exit(0);}
        });

        entryField.addActionListener(this);

        myFrame.pack();
        myFrame.setVisible(true);
        entryField.requestFocus();
        */
        myFrame = new JFrame("One Piece Treasure Cruise");
        myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        entryField = new JTextField(34);

        log = new JTextArea();
        log.setEditable(false);
        JScrollPane listScroller = new JScrollPane(log);
        listScroller.setPreferredSize(new Dimension(640, 200));
        listScroller.setMinimumSize(new Dimension(250, 100));

        panel = new JPanel();

        image = new JLabel();

        panel.setLayout(new GridBagLayout());

        gbc = new GridBagConstraints();

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridheight = 1;
        // gbc.gridwidth=6;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridwidth = GridBagConstraints.PAGE_END;
        panel.add(image, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridheight = 7;
        gbc.gridwidth = 1;
        panel.add(listScroller, gbc);

        gbc.gridx = 0;
        gbc.gridy = 8;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        panel.add(entryField, gbc);

        JLabel label = new JLabel("Direction Button ", JLabel.CENTER);
        gbc.gridx = 2;
        gbc.gridy = 2;
        gbc.gridheight = 1;
        gbc.gridwidth = 3;
        panel.add(label, gbc);


        north = new JButton("North");
        north.setPreferredSize(new Dimension(100, 20));
        gbc.gridx = 3;
        gbc.gridy = 3;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        north.addActionListener(this);
        panel.add(north, gbc);

        west = new JButton("West");
        west.setPreferredSize(new Dimension(120, 20));
        gbc.gridx = 2;
        gbc.gridy = 4;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        west.addActionListener(this);
        panel.add(west, gbc);

        none = new JButton(" ");
        none.setPreferredSize(new Dimension(120, 20));
        none.setBackground(Color.GRAY);
        gbc.gridx = 3;
        gbc.gridy = 4;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        panel.add(none, gbc);

        east = new JButton("East");
        east.setPreferredSize(new Dimension(120, 20));
        gbc.gridx = 4;
        gbc.gridy = 4;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        east.addActionListener(this);
        panel.add(east, gbc);

        south = new JButton("South");
        south.setPreferredSize(new Dimension(120, 20));
        gbc.gridx = 3;
        gbc.gridy = 5;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        south.addActionListener(this);
        panel.add(south, gbc);
        
        chargeBeam = new JButton("Charge Beam");
        chargeBeam.setPreferredSize(new Dimension(120, 20));
        gbc.gridx = 2;
        gbc.gridy = 7;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        chargeBeam.addActionListener(this);
        panel.add(chargeBeam, gbc);
        
        fireBeam = new JButton("Fire Beam");
        fireBeam.setPreferredSize(new Dimension(120, 20));
        gbc.gridx = 4;
        gbc.gridy = 7;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        fireBeam.addActionListener(this);
        panel.add(fireBeam, gbc);

        help = new JButton("Help");
        help.setPreferredSize(new Dimension(80, 20));
        gbc.gridx = 2;
        gbc.gridy = 8;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        help.addActionListener(this);
        panel.add(help, gbc);

        back = new JButton("Back");
        back.setPreferredSize(new Dimension(60, 20));
        gbc.gridx = 3;
        gbc.gridy = 8;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        back.addActionListener(this);
        panel.add(back, gbc);

        look = new JButton("Look");
        look.setPreferredSize(new Dimension(80, 20));
        gbc.gridx = 4;
        gbc.gridy = 8;
        gbc.gridheight = 1;
        gbc.gridwidth = 1;
        look.addActionListener(this);
        panel.add(look, gbc);

        myFrame.getContentPane().add(panel, BorderLayout.CENTER);

        // add some event listeners to some components
        myFrame.addWindowListener(new WindowAdapter() {
           /* public void windowClosing(WindowEvent e) {
                Save x=new Save();
                x.clearFile();
                System.exit(0);
            }*/
        });

        entryField.addActionListener(this);
        myFrame.pack();
        myFrame.setVisible(true);
        entryField.requestFocus();
    }

    /**
     * Actionlistener interface for entry textfield.
     */
    public void actionPerformed(ActionEvent e) {
        // no need to check the type of  action at the moment.
        // there is only one possible action: text entry
        Object source = e.getSource();
        if (source == north)
            engine.interpretCommand("go north");

        else if (source == northWest)
            engine.interpretCommand("go northWest");

        else if (source == northEast)
            engine.interpretCommand("go northEast");

        else if (source == west)
            engine.interpretCommand("go west");

        else if (source == east)
            engine.interpretCommand("go east");

        else if (source == southWest)
            engine.interpretCommand("go southWest");

        else if (source == southEast)
            engine.interpretCommand("go southEast");

        else if (source == south)
            engine.interpretCommand("go south");
        
        else if (source == chargeBeam)
            engine.interpretCommand("charge");
        
        else if (source == fireBeam)
            engine.interpretCommand("fire");

        else if (source == help)
            engine.interpretCommand("help");

        else if (source == look)
            engine.interpretCommand("look");

        else if (source == back)
            engine.interpretCommand("back");

        else
            processCommand();
    }

    public GameEngine getEngine() {
        return engine;
    }
    /**
     * A command has been entered. Read the command and do whatever is 
     * necessary to process it.
     */
    private void processCommand()
    {
        boolean finished = false;
        String input = entryField.getText();
        entryField.setText("");
        engine.interpretCommand(input);
    }
}
