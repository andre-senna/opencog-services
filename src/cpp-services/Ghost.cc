#include <opencog/util/Config.h>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "Ghost.h"

using namespace opencogservices;
using namespace std;

Ghost::Ghost() : OpencogSNETService()
{
    // Load config files
    opencog::config().load("./config/opencog_patternminer_nlp.conf");

    // Init
    name = "Betty";
}

Ghost::~Ghost()
{
}

void Ghost::talk(const std::string &msg, std::string &output)
{
    std::string command = "(map cog-name (test-ghost \"" + msg + "\" ))";
    evaluateScheme(output, command);
}

void Ghost::loadRuleFile(const std::string &name, std::string &output)
{
    bool loaded = loadAtomeseFile(output, name);

    if (!loaded)
        output = "Bot loaded successfully!";
    else
        output = "Bot not loaded, perhaps this file does not exists...";
}

unsigned int Ghost::getCommand(const std::string &cmd_str)
{
    unsigned int command = 0;

    if (cmd_str == S_TALK)
        return TALK;
    if (cmd_str == S_LOAD_RULE_FILE)
        return LOAD_RULE_FILE;

    return command;
}

void Ghost::loadModules()
{
    OpencogSNETService::loadModules();

    printf("INTERNAL LOADING...\n\n");

    // Initialize schemeeval with base libraries
    evaluateScheme("(use-modules (opencog))\
                    (use-modules (opencog nlp) (opencog nlp lg-dict) (opencog nlp relex2logic) (opencog nlp chatbot))\
                    (use-modules (opencog nlp sureal) (opencog nlp microplanning))\
                    (use-modules (opencog nlp aiml) (opencog openpsi))\ 
                    (use-modules (opencog ghost))\
                    (use-modules (opencog ghost procedures))\
                    (use-modules (opencog cogserver))");

    // Scheme - set relex host ip address into guile session into schemeval
    evaluateScheme("(set-relex-server-host)");
}

bool Ghost::execute(string &output, const vector<std::string> &args)
{
    // bot response
    std::string response = "";

    // Send startup message after receiving an empty argument list
    if (args.size() == 0)
    {
        output.assign("I am " + name);
        return OK;
    }

    // try to parse command if any is received
    unsigned int command = getCommand(args[0]);

    // If args < 2 it is impossible to run any command
    if (args.size() < 2)
    {
        output.assign("Insufficient arguments for the \"" + args[0] + "\" command...");
        return OK;
    }

    opencog::logger().info("Command: " + std::to_string(command));

    switch (command)
    {
    case TALK:
        talk(args[1], response);
        break;
    case LOAD_RULE_FILE:
        opencog::logger().info(args[1]);
        loadRuleFile(args[1], response);
        break;
    default:
        response = "Invalid command...";
        break;
    }

    // remove any unwanted character from the response
    boost::remove_erase_if(response, boost::is_any_of("()\n"));

    // set default response if none is obtained from the system
    if (response.length() == 0)
        response = "I have nothing to say...";

    // set output to the user
    output.append("\nThis user atomspace: " + atomspaceAddress + "\n\n");
    output.append(name + ": " + response + "\n");

    return OK;
}