#include "loadcomponent.h"
#include "projectdefines.h"
#include <sstream>

LoadComponent::LoadComponent(double fx, double fy, double mz)
{
    values = std::vector<double>({fx,fy,mz});
    types = std::vector<LoadType>({LoadType::FX,LoadType::FY,LoadType::MZ});
}

LoadComponent::LoadComponent(double fx, double fy, double fz, double mx, double my, double mz)
{
    values = std::vector<double>({fx,fy,fz,mx,my,mz});
    types = std::vector<LoadType>({LoadType::FX,LoadType::FY,LoadType::FZ,LoadType::MX,LoadType::MY,LoadType::MZ});
}

double LoadComponent::getValue(unsigned int i)
{
    return values.at(i);
}

double LoadComponent::getValueByType(LoadType type)
{
    for (uint i = 0; i < values.size(); i++) {
        if (types[i] == type) {
            return values[i];
        }
    }
    return 0;
}

void LoadComponent::setValueByType(double value, LoadType type)
{
    for (uint i = 0; i < values.size(); i++) {
        if (types[i] == type) {
            values[i] = value;
        }
    }
}

string LoadComponent::printInfo()
{
    std::stringstream ss;
    for (int i = 0; i < values.size(); i++) {
        ss << "value [" << values[i] << "] type [" << (int)types[i] << "]" << endl;
    }
    return ss.str();
}
