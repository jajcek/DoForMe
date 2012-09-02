#include "recorder_settings.h"

RecorderSettings* RecorderSettings::m_object = NULL;

RecorderSettings::RecorderSettings() {}

RecorderSettings* RecorderSettings::getInstance() {
	if( m_object )
		m_object = new RecorderSettings();

	return m_object;
}