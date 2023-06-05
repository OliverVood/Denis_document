<?php

	namespace Proj\Admin\Units\HTML;

	require DIR_UNITS . 'statistics/admin/statistics.structure.inc';
	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.html.inc';
	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.html.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;
	use Proj\Admin\Editor\HTML as Editor;

	class Statistics extends Structure\Statistics {
		use Instance;

		public Editor\Ip $editor_ip;
		public Editor\Actions $editor_act;

		private function __construct() {
			parent::__construct();

			self::$view->Push(self::$out_menu, [$this, 'OutMenu']);

			$this->editor_ip = new Editor\Ip(self::NAME . '_ip', $this->table_ip);
			$this->editor_act = new Editor\Actions(self::NAME . '_act', $this->table_act);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Статистика', [
					$this->editor_ip->select->GetLinkHref('Запросы к серверу', ['page' => 1]),
					$this->editor_act->select->GetLinkHref('Действия пользователя', ['page' => 1])
				])
			);
		}

	}

	Statistics::init();