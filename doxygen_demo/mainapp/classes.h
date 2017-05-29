#ifndef CLASSES_H
#define CLASSES_H
#include <string>

//!  A test class.
/*!
  A more elaborate class description.
*/
class QTstyle_Test
{
public:
  //! An enum.
  /*! More detailed enum description. */
  enum TEnum
  {
    TVal1, /*!< Enum value TVal1. */
    TVal2, /*!< Enum value TVal2. */
    TVal3  /*!< Enum value TVal3. */
  }
      //! Enum pointer.
      /*! Details. */
      * enumPtr,
      //! Enum variable.
      /*! Details. */
      enumVar;

  //! A constructor.
  /*!
      A more elaborate description of the constructor.
    */
  QTstyle_Test();
  //! A destructor.
  /*!
      A more elaborate description of the destructor.
    */
  ~QTstyle_Test();

  //! A normal member taking two arguments and returning an integer value.
  /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
  int testMe(int a, const char *s);

  //! A pure virtual member.
  /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
  virtual void testMeToo(char c1, char c2) = 0;

  //! A public variable.
  /*!
      Details.
    */
  int publicVar;

  //! A function variable.
  /*!
      Details.
    */
  int (*handler)(int a, int b);
};

/*!
  * \brief A basic student class, for test using doxygen.
  *
  * Here is detail description.
  */
class BaseClass
{
public:
  /*! An enum type. 
     *  The documentation block cannot be put after the enum! 
     */
  enum EnumType
  {
    int EVal1, /**< enum value 1 */
    int EVal2  /**< enum value 2 */
  };

  /*!
   * \brief default constuctor, with unique id.
   */
  explicit BaseClass(size_t id) : m_id(id) {}

protected:
  /*!
   * \brief id is a unique of BaseClass enrity.
   */
  size_t m_id;

  /*!
   * \brief BaseClass feature.
   */
  std::string m_baseFeature;
};

/*!
 * \brief high school student inherit from student.
 */
class ChildClass : public BaseClass
{
public:
  explicit ChildClass(size_t id) : BaseClass(id) {}
  void setChildFeature(std::string &feature) { m_childFeature = feature; }
  void memberFunction() {}
  std::string getChildFeature() { return m_childFeature; }

private:
  std::string m_childFeature; /*!< Child feature */
};

#endif //CLASSES_H