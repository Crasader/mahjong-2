#include "srcommon.h"

QString sr::convertCard(BYTE card)
{

   BYTE card_type = card & 0xF0;

   BYTE card_num = card & 0x0F;

   QString name;

   switch (card_type) {
   case 0x00:
       name = QStringLiteral(" ��");
       break;
   case 0x10:
       name = QStringLiteral(" ��");
       break;
   case 0x20:
       name = QStringLiteral(" ͬ");
       break;
   case 0x30:
       name = QStringLiteral(" ��");
       break;
   default:
       break;
   }

   name = QString::number(card_num) + name;

   return name;
}


const char* const sr::getDirectionNameC(enDirection direction)
{
    switch (direction) {
    case ::enDirection::South:
        return "λ��";
    case ::enDirection::West:
        return "λ��";
    case ::enDirection::North:
        return "λ��";
    case ::enDirection::East:
        return "λ��";
    default:
        return "????";
    }
}

QString sr::getDirectionNameQ(enDirection direction)
{
    switch (direction) {
    case ::enDirection::South:
        return QStringLiteral("λ��");
    case ::enDirection::West:
        return QStringLiteral("λ��");
    case ::enDirection::North:
        return QStringLiteral("λ��");
    case ::enDirection::East:
        return QStringLiteral("λ��");
    default:
        return QStringLiteral("????");
    }
}
