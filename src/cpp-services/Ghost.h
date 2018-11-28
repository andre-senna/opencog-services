#ifndef GHOST_SERVICE_H
#define GHOST_SERVICE_H

#include <opencog/util/Config.h>
#include <opencog/atomspace/AtomSpace.h>
#include <opencog/learning/PatternMiner/PatternMiner.h>
#include <opencog/guile/SchemeEval.h>

#include "../OpencogSNETService.h"

#define S_TALK "talk"
#define S_CREATE_ATOMSPACE "create brain"
#define S_DELETE_ATOMSPACE "delete brain"
#define S_CLEAR_ATOMSPACE "erase memory"
#define S_CHANGE_ATOMSPACE "change brain"
#define S_LOAD_RULE_FILE "load"
#define S_DELETE_RULE "delete memory"
#define S_ADD_RULE "add memory"
#define S_GUILE_SHELL "guile"
#define S_BAD_PROFILE "cheat_xxx"

#define TALK 210
#define CREATE_ATOMSPACE 211
#define DELETE_ATOMSPACE 212
#define CLEAR_ATOMSPACE 213
#define CHANGE_ATOMSPACE 214
#define LOAD_RULE_FILE 215
#define DELETE_RULE 216
#define ADD_RULE 217
#define GUILE_SHELL 218

#define BAD_PROFILE 100

#define ERRO true
#define OK false

namespace opencogservices
{
class Ghost : public OpencogSNETService
{
public:
  Ghost();
  ~Ghost();

  /** Brief description of foo.
     * 
     * An optional and more in depth description of foo
     *
     * @param output String returned as a response from the service.
     * @param args Arguments passed to the service to be performed.
     * @return Returns false if the service performed just right.
     *
     * @bug A bug with foo (should really be in the Github issue tracker!)
     * @todo something missing from the implementation of foo (this gets
     *       added to a global todo list, very handy)
     */
  bool execute(std::string &output, const std::vector<std::string> &args) override;

  /** Brief description of foo.
     * 
     * An optional and more in depth description of foo
     *
     * @param output String returned as a response from the service.
     * @param args Arguments passed to the service to be performed.
     * @return Returns false if the service performed just right.
     *
     * @bug A bug with foo (should really be in the Github issue tracker!)
     * @todo something missing from the implementation of foo (this gets
     *       added to a global todo list, very handy)
     */
  void loadModules() override;

  /** Brief description of foo.
     * 
     * An optional and more in depth description of foo
     *
     * @param output String returned as a response from the service.
     * @param args Arguments passed to the service to be performed.
     * @return Returns false if the service performed just right.
     *
     * @bug A bug with foo (should really be in the Github issue tracker!)
     * @todo something missing from the implementation of foo (this gets
     *       added to a global todo list, very handy)
     */
  void talk(const std::string &msg, std::string &output);

  /** Brief description of foo.
     * 
     * An optional and more in depth description of foo
     *
     * @param output String returned as a response from the service.
     * @param args Arguments passed to the service to be performed.
     * @return Returns false if the service performed just right.
     *
     * @bug A bug with foo (should really be in the Github issue tracker!)
     * @todo something missing from the implementation of foo (this gets
     *       added to a global todo list, very handy)
     */
  void loadRuleFile(const std::string &name, std::string &output);

  /** Brief description of foo.
     * 
     * An optional and more in depth description of foo
     *
     * @param output String returned as a response from the service.
     * @param args Arguments passed to the service to be performed.
     * @return Returns false if the service performed just right.
     *
     * @bug A bug with foo (should really be in the Github issue tracker!)
     * @todo something missing from the implementation of foo (this gets
     *       added to a global todo list, very handy)
     */
  unsigned int getCommand(const std::string &cmd_str);

private:
  std::string name;
  std::string atomspaceAddress;
};
} // namespace opencogservices
#endif