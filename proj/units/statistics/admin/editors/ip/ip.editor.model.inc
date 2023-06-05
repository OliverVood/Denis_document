<?php

	namespace Proj\Admin\Editor\Model;

	use Base\Controller;
	use Base\Editor\Skins\Browse;

	trait Ip {

		private function Init(): void {
			$this->titleSelect = 'Статистика запросов к серверу';

			$this->querySelect->order('datecr', 'DESC')->order('id', 'DESC');
		}

		protected function RegActions(): void {
			$this->RegActionSelect();
		}

		protected function SetHandlers(): void {
			Controller::$view->Push($this->select, [$this, 'OnSelect']);
		}

		protected function ManageSelect(): array {
			return [];
		}

		protected function FieldsSelect(): array {
			return [
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'uid'		=> new Browse\Text('Пользователь'),
				'ip'		=> new Browse\Int2IP('IP адрес'),
				'path'		=> new Browse\Text('Путь'),
				'params'	=> new Browse\Text('Параметры')
			];
		}

	}