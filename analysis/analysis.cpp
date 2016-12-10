#include "analysis.h"
Analysis::Analysis()
{
    mStatus = Analysis::Success;
}

Analysis::Status Analysis::status() const
{
    return mStatus;
}

void Analysis::setStatus(const Status &status)
{
    mStatus = status;
}

QIcon Analysis::statusIcon() const
{
    if (mStatus == Analysis::Success)
        return QIcon(":/accept_button.png");
    if (mStatus == Analysis::Error)
        return QIcon(":/exclamation.png");
    if (mStatus == Analysis::Warning)
        return QIcon(":/warning.png");

    return QIcon();

}

