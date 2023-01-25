<?php

	namespace Proj\Admin\Units;

	require 'statistics.structure.inc';

	use Base\Instance;
	use Base\Controller;
	use Base\Action;
	use Base\Editor\EditorMySQLi;
	use Proj\Admin\Structure;
	use Proj\Admin\Templates\Layout;
	use Proj\Admin\Templates\General\Group;

	class Statistics extends Structure\Statistics {
		use Instance;

		private EditorMySQLi $editor_ip;
		private EditorMySQLi $editor_act;

		private Action $out_menu;

		private function __construct() {
			parent::__construct();

			$this->editor_ip = new EditorMySQLi(self::NAME . 'ip', $this->table_ip, [
				'titles' => [
					'select' => 'Статистика запросов к серверу'
				],
				'order' => [
					'datecr DESC',
					'id DESC'
				],
				'select' => [
					'datecr' => 'Дата',
					'uid' => 'Пользователь',
					'ip_part_I' => 'IP часть I',
					'ip_part_II' => 'IP часть II',
					'ip_part_III' => 'IP часть III',
					'ip_part_IV' => 'IP часть IV',
					'path' => 'Основной путь',
					'params' => 'Параметры'
				]
			]);

			$this->editor_act = new EditorMySQLi(self::NAME . '_act', $this->table_act, [
				'titles' => [
					'select' => 'Статистика действий пользователя'
				],
				'order' => [
					'datecr DESC',
					'id DESC'
				],
				'select' => [
					'datecr' => 'Дата',
					'uid' => 'Пользователь',
					'object' => 'Объект',
					'action' => 'Действие',
					'params' => 'Параметры'
				]
			]);

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