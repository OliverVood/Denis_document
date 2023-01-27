<?php

	namespace Proj\Admin\Units;

	require 'statistics.structure.inc';
	require 'actions.editor.inc';
	require 'ip.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Statistics extends Structure\Statistics {
		use Instance;

		private EditorMySQLi $editor_ip;
		private EditorMySQLi $editor_act;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_ip = new Editor\Ip(self::NAME . 'ip', $this->table_ip);
			$this->editor_act = new Editor\Actions(self::NAME . '_act', $this->table_act);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::object()->ToVar('Статистика', [
					$this->editor_ip->select->GetLink('Запросы к серверу'),
					$this->editor_act->select->GetLink('Действия пользователя')
				])
			);
		}

	}

	Statistics::init();