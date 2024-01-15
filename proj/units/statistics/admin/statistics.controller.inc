<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'statistics/admin/statistics.structure.inc';

	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.inc';
	require DIR_UNITS . 'statistics/admin/editors/actions/actions.editor.inc';

	use Base\Instance;
	use Proj\Admin\Structure;
	use Proj\Admin\Editor;
	use Proj\Editor\Consts as EditorConsts;

	class Statistics extends Structure\Statistics {
		use Instance;

		public Editor\Ip $editor_ip;
		public Editor\Actions $editor_act;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->editor_ip = new Editor\Ip(EditorConsts\ID_STATISTICS_IP, self::NAME . '_ip', $this->table_ip, 'Статистика запросов (редактор)');
			$this->editor_act = new Editor\Actions(EditorConsts\ID_STATISTICS_ACTIONS, self::NAME . '_act', $this->table_act, 'Статистика действий (редактор)');
		}

		public function GetMenu(): array {
			$out = [];
			if ($this->editor_ip->Allow($this->editor_ip::ACCESS_SELECT)) $out[] = $this->editor_ip->select->GetLinkHref('Запросы к серверу', ['page' => 1]);
			if ($this->editor_act->Allow($this->editor_act::ACCESS_SELECT)) $out[] = $this->editor_act->select->GetLinkHref('Действия клиента', ['page' => 1]);

			return $out;
		}

	}

	Statistics::init();