#ifndef LVK_NLP_EXACTMATCHENGINE_H
#define LVK_NLP_EXACTMATCHENGINE_H

#include "nlpengine.h"

namespace Lvk
{

namespace Nlp
{

class ExactMatchEngine : public Engine
{
public:
    ExactMatchEngine();

    ~ExactMatchEngine();

    virtual const RuleList &rules() const;

    virtual RuleList &rules();

    virtual void setRules(const RuleList &rules);

    virtual QString getResponse(const QString &input);

    virtual QString getResponse(const QString &input, RuleList &matched);

private:

    RuleList m_rules;
};

} // namespace Nlp

} // namespace Lvk

#endif // EXACTMATCHENGINE_H
