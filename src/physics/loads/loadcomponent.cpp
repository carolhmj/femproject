#include "loadcomponent.h"
#include "projectdefines.h"

#include <sstream>

LoadComponent::LoadComponent(double fx, double fy, double mz)
{
    values = std::vector<double>({fx,fy,0,0,0,mz});
    types = std::vector<LoadType>({LoadType::FORCE,LoadType::FORCE,LoadType::FORCE,LoadType::MOMENTUM,LoadType::MOMENTUM,LoadType::MOMENTUM});
}

LoadComponent::LoadComponent(double fx, double fy, double fz, double mx, double my, double mz)
{
    values = std::vector<double>({fx,fy,fz,mx,my,mz});
    types = std::vector<LoadType>({LoadType::FORCE,LoadType::FORCE,LoadType::FORCE,LoadType::MOMENTUM,LoadType::MOMENTUM,LoadType::MOMENTUM});
}

double LoadComponent::getValue(unsigned int i)
{
    return values.at(i);
}

string LoadComponent::printInfo()
{
    std::stringstream ss;
    for (int i = 0; i < values.size(); i++) {
        ss << "value [" << values[i] << "] type [" << static_cast<int>(types[i]) << "]" << endl;
    }
    return ss.str();
}
