<?php

	namespace Proj\Admin\Units;

	require 'changes.structure.inc';
	require 'changes.editor.inc';
	require 'change.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor;

	class Changes extends Structure\Changes {
		use Instance;

		private EditorMySQLi $editor_changes;
		public EditorMySQLi $editor_change;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_changes = new Editor\Changes(self::NAME, $this->table_changes);
			$this->editor_change = new Editor\Change('change', $this->table_change);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Изменения', [
					$this->editor_changes->select->GetLink('Списки изменений'),
					$this->editor_changes->create->GetLink('Добавить список изменений')
				])
			);
		}

	}

	Changes::init();