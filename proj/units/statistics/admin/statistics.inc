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
		public Action $edit_ips;

		private function __construct() {
			parent::__construct();

			$this->editor_ip = new Editor\Ip(self::NAME . 'ip', $this->table_ip);
			$this->editor_act = new Editor\Actions(self::NAME . '_act', $this->table_act);

			$this->out_menu = new Action();
			$this->edit_ips = new Action(self::NAME, 'edit_ips');

			Controller::instance()->view->Push($this->out_menu, [$this, 'OutMenu']);
			Controller::instance()->view->Push($this->edit_ips, [$this, 'EditIps']);
		}

		public function OutMenu() {
			Layout::instance()->menu->Push(
				Group::ToVar('Статистика', [
					$this->editor_ip->select->GetLink('Запросы к серверу'),
					$this->editor_act->select->GetLink('Действия пользователя')
				])
			);
		}

		public function EditIps() {
			$result = $this->table_ip->Select(['id', 'ip_part_I', 'ip_part_II', 'ip_part_III', 'ip_part_IV']);
			$items = $this->table_ip->FetchAll($result);
			foreach ($items as $item) $this->table_ip->Update(['ip' => ip2long("{$item['ip_part_I']}.{$item['ip_part_II']}.{$item['ip_part_III']}.{$item['ip_part_IV']}")], "`id` = {$item['id']}");
		}

	}

	Statistics::init();