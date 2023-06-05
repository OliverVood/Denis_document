<?php

	namespace Proj\Admin\Editor\Model;

	use Base\Editor\Skins\Browse;
	use Base\Editor\Skins\Edit;
	use Proj\Units\Consts;

	trait Changes {

		private function Init(): void {
			$this->titleSelect = 'Списки актуального';
			$this->titleCreate = 'Добавить список актуального';
			$this->titleUpdate = 'Редактировать список актуального';
			$this->titleDelete = 'Удалить список актуального?';

			$this->querySelect->where('`state` != ' . Consts\Changes::STATE_DELETE)->order('datecr', 'DESC')->order('id');
		}

		protected function FieldsSelect(): array {
			return [
				'id'			=> new Browse\Text('#'),
				'state'			=> new Browse\ValueFromArray('Состояние', Consts\Changes::STATES_VIEW),
				'datepb'		=> new Browse\DateFormat('Дата публикации', 'd.m.Y H:i'),
				'work_header'	=> new Browse\Text('Рабочий заголовок'),
				'header'		=> new Browse\Text('Заголовок'),
			];
		}

		protected function FieldsCreate(): array {
			return [
				'state'			=> new Edit\Hidden('Состояние', 'form[state]', Consts\Changes::STATES['draft']),
				'work_header'	=> new Edit\Text('Рабочий заголовок', 'form[work_header]'),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'datepb'		=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

		protected function FieldsUpdate(): array {
			return [
				'state'			=> new Edit\Select('Состояние', 'form[state]', [
					Consts\Changes::STATE_DRAFT	=> 'Черновик',
					Consts\Changes::STATE_ACTIVE	=> 'Активный',
					Consts\Changes::STATE_INACTIVE	=> 'Не активный',
				]),
				'work_header'	=> new Edit\Text('Заголовок', 'form[header]'),
				'header'		=> new Edit\Text('Заголовок', 'form[header]'),
				'datepb'		=> new Edit\DateTime('Дата публикации', 'form[datepb]')
			];
		}

	}