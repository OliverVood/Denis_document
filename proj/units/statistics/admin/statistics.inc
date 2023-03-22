<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'statistics/admin/statistics.structure.inc';
	require DIR_UNITS . 'statistics/admin/actions.editor.inc';
	require DIR_UNITS . 'statistics/admin/ip.editor.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Statistics extends Structure\Statistics {
		use Instance;

		public Editor\Ip $editor_ip;
		public Editor\Actions $editor_act;

		public Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_ip = new Editor\Ip(self::NAME . 'ip', $this->table_ip);
			$this->editor_act = new Editor\Actions(self::NAME . '_act', $this->table_act);

			$this->out_menu = new Action();

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Статистика', [
					$this->editor_ip->select->GetLink('Запросы к серверу'),
					$this->editor_act->select->GetLink('Действия пользователя')
				])
			);
		}

	}

	Statistics::init();