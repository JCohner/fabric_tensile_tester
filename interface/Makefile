SHELL:=/bin/bash
VERSION=0x03

.PHONY: designer
designer:
	@pyqt6-tools designer app.ui

.PHONY: update_app_schema
update_app_schema:
	@pyuic6 -x app.ui -o qt_app_schema.py

.PHONY: run_ui
run_ui:
	@source venv/bin/activate && python3 ui.py