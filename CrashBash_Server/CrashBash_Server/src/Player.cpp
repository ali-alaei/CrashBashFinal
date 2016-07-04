#include "../include/Player.h"
#include <iostream>
Player::Player(int x,int y):xPos(x),yPos(y)
{
    this->throwSpeed=5;
    this->throwRate=100;
    this->health=3;
    this->direction=2;
    this->speed=20;
    this->ownBox=0;
    this->deadOrAlive=1;
}

Player::~Player()
{
    //dtor
}

bool Player::playerBox()
{
    std::cout<<this->space<<std::endl;
    if(this->ownBox==0)
    {
        if(this->space==1)
        {
            std::cout<<"KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK";

            for(int i=0;i<normalBoxesNum;i++)
            {
                if(yPos-30<=normalBoxes[i]->getYPos()+60 && yPos-30>normalBoxes[i]->getYPos())
                    if(xPos<=normalBoxes[i]->getXPos()+60 && xPos>normalBoxes[i]->getXPos()-60)
                    {
                        return true;
                    }

                if(yPos+20<=normalBoxes[i]->getYPos()+60 && yPos+20>normalBoxes[i]->getYPos())
                    if(xPos+10<=normalBoxes[i]->getXPos()+60 && xPos+10>normalBoxes[i]->getXPos()-60)
                    {
                        return true;
                    }

                if(yPos+60<=normalBoxes[i]->getYPos()+60 && yPos+60>normalBoxes[i]->getYPos())
                    if(xPos<=normalBoxes[i]->getXPos()+60 && xPos>normalBoxes[i]->getXPos()-60)
                {
                    return true;
                }
                if(yPos+30<=normalBoxes[i]->getYPos()+60 && yPos+30>normalBoxes[i]->getYPos())
                    if(xPos-40<=normalBoxes[i]->getXPos()+60 && xPos-40>normalBoxes[i]->getXPos()-60)
                    {
                        return true;
                    }
             }
        }
    }
    return false;
}

void Player::changePosUp()
{
    this->yPos-=speed;
}


void Player::changePosDown()
{
    this->yPos+=speed;
}



void Player::changePosRight()
{
    this->xPos+=speed;
}


void Player::changePosLeft()
{
    this->xPos-=speed;
}


void Player::changePosUR()
{
    this->xPos+=speed;
    this->yPos-=speed;
}


void Player::changePosUL()
{
    this->xPos-=speed;
    this->yPos-=speed;
}


void Player::changePosDR()
{
    this->xPos+=speed;
    this->yPos+=speed;
}


void Player::changePosDL()
{
    this->xPos-=speed;
    this->yPos+=speed;
}

void Player::catchBox()
{
    std::cout<<"LLLLLLLLLLLL";
    ownBox=1;
    tokenBox->setOwner(1);
    tokenBox->setDirection(this->direction);
    tokenBox->setSpeed(this->speed);
}

void Player::throwBox()
{
    if(ownBox==1)
    {
        std::cout<<"RRRRRRRRR";
        if(this->space==1)
        {
            std::cout<<"TTTTTTTTTTTT";
            tokenBox->setDirection(this->direction);
            tokenBox->setSpeed(this->throwSpeed);
            tokenBox->setRate(this->throwRate);
            tokenBox->setIsThrow(1);
            ownBox=0;
        }
     }
}


void Player::increasePlayerHealth()
{
    this->health+=1;
}

void Player::decreasePlayerHealth()
{
    this->health-=1;
}

void Player::setNormalBoxesNum(int x)
{
    this->normalBoxesNum=x;
}

void Player::setDirection(int x)
{
    this->direction=x;
}

void Player::increaseSpeed()
{
    this->speed+=3;
}

void Player::increaseSpeedRate()
{
    this->throwSpeed+=3;
}

void Player::increaseThrowRate()
{
    this->throwRate+=3;
}

//void Player::setInputData(Input input)
//{
//    this->inputData=&input;
//}

//void Player::setTokenBox(NoramlBox normalbox)
//{
 //   this->tokenBox=&normalbox;
//}

void Player::setGiftBoxVector(std::vector <GiftBox> &gifts)
{
    for(int i=0;i<giftBoxesNum;i++)
    {
        giftBoxes.push_back(&gifts[i]);
    }
}

void Player::setTntBoxes(std::vector <TntBox> &tnts)
{
    for(int i=0;i<tntBoxesNum;i++)
    {
        tntBoxes.push_back(&tnts[i]);
    }
}

void Player::setNoramlBoxVector(std::vector <NoramlBox> &normals)
{
    for(int i=0;i<normalBoxesNum;i++)
    {
        normalBoxes.push_back(&normals[i]);
    }
}

bool Player::playerCollisionGiftBox()
{
    for(int i=0;i<giftBoxesNum;i++)
    {
        if(yPos<=giftBoxes[i]->getYPos()+60 && yPos>=giftBoxes[i]->getYPos())
            if(xPos<=giftBoxes[i]->getXPos()+60 && xPos>=giftBoxes[i]->getXPos()-60)
            {
                this->earnedBox=giftBoxes[i];
                earnedBox->deadOrAlive = 0;
                return true;
            }
    }

    return false;
}


bool Player::playerCollisionTntBox()
{
    for(int i=0;i<tntBoxesNum;i++)
    {
        if(yPos<=tntBoxes[i]->getYPos()+60 && yPos>=tntBoxes[i]->getYPos())
            if(xPos<=tntBoxes[i]->getXPos()+60 && xPos>=tntBoxes[i]->getXPos()-60)
            {
                    this->collisionBox=tntBoxes[i];
                    collisionBox->deadOrAlive=0;
                    return true;
            }
    }
    return false;
}
bool Player::OwnedBox()
{

    return this->ownBox;

}

int Player::getXPos()
{
    return this->xPos;
}

int Player::getYPos()
{
    return this->yPos;
}

int Player::getPlayerHealth()
{
    return this->health;
}


int Player::checkCollisionToBox()
{
   // std::cout<<"JJJJJJJJJJJJJJJJJJJJJ\n";
    if(direction==1)
    {
        for(int i=0;i<normalBoxesNum;i++)
        {
            if(yPos-30<=normalBoxes[i]->getYPos()+60 && yPos-30>normalBoxes[i]->getYPos())
                if(xPos<=normalBoxes[i]->getXPos()+60 && xPos>normalBoxes[i]->getXPos()-60)
                {
                    return 1;
                }

        }
        return 0;
    }
    else if(direction==2)
    {
        for(int i=0;i<normalBoxesNum;i++)
        {
        if(yPos+20<=normalBoxes[i]->getYPos()+60 && yPos+20>normalBoxes[i]->getYPos())
                if(xPos+10<=normalBoxes[i]->getXPos()+60 && xPos+10>normalBoxes[i]->getXPos()-60)
                {
                    return 2;
                }
        }
        return 0;

    }
    else if(direction==3)
    {
        for(int i=0;i<normalBoxesNum;i++)
        {
            if(yPos+60<=normalBoxes[i]->getYPos()+60 && yPos+60>normalBoxes[i]->getYPos())
                if(xPos<=normalBoxes[i]->getXPos()+60 && xPos>normalBoxes[i]->getXPos()-60)
                {
                    return 3;
                }
        }
        return 0;

    }

    else if(direction==4)
    {
        for(int i=0;i<normalBoxesNum;i++)
        {
            if(yPos+30<=normalBoxes[i]->getYPos()+60 && yPos+30>normalBoxes[i]->getYPos())
                if(xPos-40<=normalBoxes[i]->getXPos()+60 && xPos-40>normalBoxes[i]->getXPos()-60)
                {
                    return 4;
                }
        }
        return 0;
    }

}

int Player::getDirection()
{
    return this->direction;
}

int Player::getId()
{
    return this->id;
}
void Player::setGiftBoxesNum(int giftBoxes)
{
    this->giftBoxesNum = giftBoxes;

}
void Player::setTntBoxesNum(int tntBoxes)
{
    this->tntBoxesNum = tntBoxes;

}

void Player::setSpace(bool a)
{
    this->space=a;
}

void Player::setId(int a)
{

    this->id = a;
}

int Player::checkCollisionToWall()
{
     if(this->yPos<60)
    {
        return 1;
    }

    else if(this->xPos >1163)

    {
        return 2;
    }



    else if(this->yPos  > 833)
    {
        return 3;
    }


    else if(this->xPos<80)
    {
        return 4;
    }

    else return 0;
}


