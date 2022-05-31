#include "numview.h"

#include <string>

grc::numview::numview(grc::rect f, std::vector<int> numList, int defaultNum) : view(f, numList[0])
{
    this->numListImage = numList;
    this->num = defaultNum;
}

bool grc::numview::render(long long tick)
{
    std::string text = std::to_string(num);
    double oneSize = frame.size.height / 2.0;
    double totalSize = text.size() * oneSize / 2.0;

    auto c = frame.center();
    auto f = grc::rect(c.x - totalSize, frame.location.y, c.x + totalSize, frame.location.y + frame.size.height);

    for (int i = 0; i < text.size(); i++) {
        int numId = this->numListImage[(text[i] - '0') % numListImage.size()];
        drawImage(grc::rect(f.location.x + (oneSize * i), f.location.y,
                            f.location.x + (oneSize * i), f.location.y + f.size.height), numId);
    }

    return false;
}
