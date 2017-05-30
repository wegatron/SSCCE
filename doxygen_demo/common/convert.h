#ifndef CONVERT_H
#define CONVERT_H

/** \ingroup common
    @{
*/

#include "common.h"

//! A ChildCommon class inherit from BaseCommon class.
/*!
    ChildCommon Class descriptions.
 */
class ChildCommon : public BaseCommon
{
  public:
    //! A testfunction to use callgraph.
    /*!
        \callgraph
        A detail description for Testfunction
     */
    void TestFunction()
    {
        preconpute();
        solve();
        clear();
    }

  private:
    void preConpute() {}
    void solve() {}
    void clear() {}
};

/**
    @}
*/
#endif //CONVERT_H