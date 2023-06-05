<?php

	namespace Proj\Units\Consts;

	interface Changes {
		const ID						= ID_CHANGES;
		const NAME						= 'changes';

		const TABLES = [
			'changes' 				=> self::NAME,
			'change'				=> 'change'
		];

		const STATE_ERROR				= 0;
		const STATE_DRAFT				= 1;
		const STATE_ACTIVE				= 2;
		const STATE_INACTIVE			= 3;
		const STATE_DELETE				= 100;

		const STATES = [
			'error'						=> self::STATE_ERROR,
			'draft'						=> self::STATE_DRAFT,
			'active'					=> self::STATE_ACTIVE,
			'inactive'					=> self::STATE_INACTIVE,
			'delete'					=> self::STATE_DELETE
		];

		const STATES_VIEW = [
			self::STATE_ERROR			=> 'Ошибка',
			self::STATE_DRAFT			=> 'Черновик',
			self::STATE_ACTIVE			=> 'Активный',
			self::STATE_INACTIVE		=> 'Не активный',
			self::STATE_DELETE			=> 'Удалён'
		];

		const PATH_COVER				= DIR_RESOURCE_IMAGE . 'changes/';
		const PATH_COVER_RELATIVE		= '/proj/resource/image/changes/';
	}