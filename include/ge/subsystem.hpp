#ifndef GE_SUBSYSTEM_HPP
#define GE_SUBSYSTEM_HPP

#pragma once

namespace ge
{
struct runtime;

struct subsystem {
	
	virtual ~subsystem() {};
	
	virtual bool update() {};
	virtual bool shutdown() {};
	
	runtime* m_runtime;
	
};

} // ge

#endif // GE_ASSET_HPP
