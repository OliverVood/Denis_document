<?php

	namespace Proj\Units\Consts;

	interface Feedback {
		const ID						= ID_FEEDBACK;
		const NAME						= 'feedback';
		const TITLE						= 'Обратная связь';

		const TABLES = [
			'feedback'					=> self::NAME
		];

		const STATE_ERROR				= 0;
		const STATE_NEW					= 1;
		const STATE_DONE				= 2;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'new'						=> self::STATE_NEW,
			'done'						=> self::STATE_DONE,
			'delete'					=> self::STATE_DELETE
		];

		const STATES_VIEW = [
			self::STATE_ERROR			=> 'Ошибка',
			self::STATE_NEW				=> 'Новая',
			self::STATE_DONE			=> 'Проверена',
			self::STATE_DELETE			=> 'Удалена'
		];

	}