#ifndef GE_SUBSYSTEM_HPP
#define GE_SUBSYSTEM_HPP

#pragma once

namespace ge
{
struct runtime;

struct subsystem {
	virtual ~subsystem(){};

    virtual bool update(){ return true; };
    virtual bool shutdown(){ return true; };

	runtime* m_runtime;
};

}  // ge

#endif  // GE_ASSET_HPP
