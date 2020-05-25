import java.util.HashMap;
import java.util.Iterator;

/*
 * This class is the main class of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.
 * 
 * This class holds a collection of all command words known to the game.
 * It is used to recognise commands as they are typed in.
 *
 * @author  Michael Kolling and David J. Barnes
 * @version 2.0 (December 2002)
 */

public class CommandWords
{
    private HashMap commands;

    /**
     * Constructor - initialise the command words.
     */
    public CommandWords()
    {
        commands = new HashMap();
        commands.put("go", new GoCommand());
        commands.put("help", new HelpCommand(this));
        commands.put("quit", new QuitCommand());
    }

    /**
     * Given a command word, find and return the matching command object.
     * Return null if there is no command with this name.
     */
    public Command get(String word)
    {
        return (Command)commands.get(word);
    }

    /*
     * Print all valid commands to System.out.
     */
    public void showAll() 
    {
        for(Iterator i = commands.keySet().iterator(); i.hasNext(); ) {
            System.out.print(i.next() + "  ");
        }
        System.out.println();
    }
}
