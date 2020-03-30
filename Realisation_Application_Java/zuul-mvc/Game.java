import java.util.Observable;
import java.util.Observer;

/**
 *  This class is the main class of the "World of Zuul" application. 
 *  "World of Zuul" is a very simple, text based adventure game.  Users 
 *  can walk around some scenery. That's all. It should really be extended 
 *  to make it more interesting!
 * 
 *  To play this game, create an instance of this class and call the "play"
 *  method.
 * 
 *  This main class creates and initialises all the others: it creates all
 *  rooms, creates the parser and starts the game.  It also evaluates and
 *  executes the commands that the parser returns.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0 (February 2002)
 */

public class Game 
{
    private Parser parser;
    private GameModel gameModel;
    private TextView textView;
    
    /**
     * Create the game and initialise its internal map.
     */
    public Game() 
    {
        gameModel = new GameModel();
        textView = new TextView(gameModel);
        gameModel.addObserver(textView);
        parser = new Parser();
    }

   
    /**
     *  Main play routine.  Loops until end of play.
     */
    public void play() 
    {        
        textView.printWelcome();
        textView.show("Type 'help' if you need help.");
        
        // Enter the main command loop.  Here we repeatedly read commands and
        // execute them until the game is over.
                
        boolean finished = false;
        while (! finished) {
            Command command = parser.getCommand();
            finished = processCommand(command);
        }
        
        textView.printGoodBye();
    }   
   
    /**
     * Given a command, process (that is: execute) the command.
     * If this command ends the game, true is returned, otherwise false is
     * returned.
     */
    private boolean processCommand(Command command) 
    {
        boolean wantToQuit = false;

        if(command.isUnknown()) {
            textView.show("I don't know what you mean...");
            return false;
        }

        String commandWord = command.getCommandWord();
        if (commandWord.equals("help"))
            printHelp();
        else if (commandWord.equals("go"))
            goRoom(command);
        else if (commandWord.equals("quit"))
            wantToQuit = quit(command);

        return wantToQuit;
    }
    // implementations of user commands:

    /**
     * Print out some help information.
     * Here we print some stupid, cryptic message and a list of the 
     * command words.
     */
    private void printHelp() 
    {
        textView.printHelp();
        textView.show("\nYour command words are:");
        textView.show(parser.getCommandList());
    }

    /** 
     * Try to go to one direction. If there is an exit, enter
     * the new room, otherwise print an error message.
     */
    private void goRoom(Command command) 
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
            textView.show("Go where?");
            return;
        }

        String direction = command.getSecondWord();

        // Try to leave current room.
        Room nextRoom = null;
        if(direction.equals("north"))
            nextRoom = gameModel.getCurrentRoom().getExit("north");
        if(direction.equals("east"))
            nextRoom = gameModel.getCurrentRoom().getExit("east");
        if(direction.equals("south"))
            nextRoom = gameModel.getCurrentRoom().getExit("south");
        if(direction.equals("west"))
            nextRoom = gameModel.getCurrentRoom().getExit("west");
        
        if (nextRoom == null)
            textView.show("There is no door!");
        else {
            gameModel.goRoom(nextRoom);
            //printLocationInfo(); this is done automaically via the model event.
        }
    }

    /** 
     * "Quit" was entered. Check the rest of the command to see
     * whether we really quit the game. Return true, if this command
     * quits the game, false otherwise.
     */
    private boolean quit(Command command) 
    {
        if(command.hasSecondWord()) {
            textView.show("Quit what?");
            return false;
        }
        else
            return true;  // signal that we want to quit
    }    
}
