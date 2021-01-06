

namespace O
{
namespace data
{
    template<class T>
    Tree<T>::Tree()
    {

    }
    template<class T>
    Tree<T>::Tree(T value)
    {
        this->value = value;
    }

    template<class T>
    std::vector<Tree<T>> Tree<T>::getChilds() const
    {
        return childs;
    }
    template<class T>
    std::vector<T> Tree<T>::getChildsValues() const
    {
        std::vector<T> res;
        for (size_t i = 0; i < childs.size(); i++)
        {
            res.push_back(childs[i].value);
        }
        return res;
    }

    template<class T>
    void Tree<T>::addChild(T value)
    {
        childs.emplace_back(value);
    }

    template<class T>
    int Tree<T>::addChildUnder(T value, T parent)
    {
        return this->addChildUnder(value, parent, 0);
    }

    template<class T>
    int Tree<T>::addChildUnder(T value, T parent, int lvlRecur)
    {
        if (this->value == value)
        {
            this->addChild(value);
            return lvlRecur + 1;
        }
        for (size_t i = 0; i < childs.size(); i++)
        {
            int v = childs[i].addChildUnder(value, parent, lvlRecur + 1);
            if (v != -1) return v;
        }
        return -1;
    }


    template<class T> 
    int Tree<T>::addChildFromRelation(T value, double (*func)(T, T))
    {
        return this->addChildFromRelation(value, func, 1);
    }

    template<class T> 
    int Tree<T>::addChildFromRelation(T value, double (*func)(T, T), int lvlRecur)
    {
        double maxScore = -1;
        Tree<T>* best = nullptr; 
        for (size_t i = 0; i < childs.size(); i++)
        {
            double score = func(this->childs[i].value, value);
            if (score != -1 && score > maxScore)
            {
                if (childs[i].addChildFromRelation(value, func, lvlRecur + 1) == -1)
                {
                    best = &(childs.at(i));
                    maxScore = score;
                }
            }
        }
        std::cout <<"v : "<< value<<" "<< lvlRecur<<" "<<maxScore <<std::endl;
        if (maxScore != -1)
        {
            best->addChild(value);
            return lvlRecur + 1;
        }
        else if (lvlRecur == 1)
        {
            if (func(this->value, value) != -1)
            {
                this->addChild(value);
                return lvlRecur;
            }
        }
        return -1;
    }

}
}